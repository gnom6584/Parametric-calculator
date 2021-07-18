//
// Created by Name on 14.07.2021.
//

#ifndef EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_DECLARATIONS_CALCULATOR_HPP_
#define EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_DECLARATIONS_CALCULATOR_HPP_

#include "calculator.hpp"
#include "declarations_stack.hpp"

#include "../tree/expression.hpp"
#include "../tree/number.hpp"
#include "../tree/parameter.hpp"
#include "../tree/function_invocation.hpp"

#include "../substituted_elements/internal_function.hpp"
#include "../substituted_elements/expression_function.hpp"

namespace expression_system::calculator {

template <typename T>
class DeclarationsCalculator final : public Calculator<T> {
public:

	[[nodiscard]] DeclarationsContainer<T>& declarations();

	[[nodiscard]] const DeclarationsContainer<T>& declarations() const;

	[[nodiscard]] T evaluate(const tree::Expression<T>& expression) const override;

private:
	[[nodiscard]] T internal_evaluate(const tree::Expression<T>& expression, const DeclarationsContainer<T>& declarations_set) const;

	DeclarationsContainer<T> _declarations;
};


//////////////////////////////////////////////////////
//                  Implementation                  //
//////////////////////////////////////////////////////


template <typename T>
DeclarationsContainer<T>& DeclarationsCalculator<T>::declarations() {
	return _declarations;
}


template <typename T>
const DeclarationsContainer<T>& DeclarationsCalculator<T>::declarations() const {
	return _declarations;
}


template <typename T>
T DeclarationsCalculator<T>::evaluate(const tree::Expression<T>& expression) const {
	return internal_evaluate(expression, _declarations);
}


template <typename T>
T DeclarationsCalculator<T>::internal_evaluate(const tree::Expression<T>& expression, const DeclarationsContainer<T>& declarations_set) const {
	using namespace std;
	using namespace tree;
	using namespace substituted_elements;

	const static auto number_type_id = typeid(Number<T>).hash_code();
	const static auto parameter_type_id = typeid(Parameter<T>).hash_code();
	const static auto function_invocation_type_id = typeid(FunctionInvocation<T>).hash_code();

	auto expression_type_id = typeid(expression).hash_code();

	if(expression_type_id == number_type_id) {
		const auto& node = static_cast<const Number<T>&>(expression);
		return node.value();
	}
	else if(expression_type_id == parameter_type_id) {
		const auto& node = static_cast<const Parameter<T>&>(expression);
		return declarations_set.get_parameter(node.name());
	}
	else if(expression_type_id == function_invocation_type_id) {
		const auto& node = static_cast<const FunctionInvocation<T>&>(expression);

		const auto arg_count = node.arguments_count();

		const auto& find = declarations_set.get_function(node.name(), arg_count);

		vector<T> evaluated_args;
		evaluated_args.reserve(arg_count);

		for (size_t i = 0; i < arg_count; ++i)
			evaluated_args.emplace_back(internal_evaluate(node[i], declarations_set));

		const auto* expression_function = dynamic_cast<const ExpressionFunction<T>*>(&find);
		if(expression_function) {

			auto function_scope = declarations_set.push();

			for (int i = 0; i < arg_count; ++i)
				function_scope.declare_parameter(expression_function->get_parameter(i), std::move(evaluated_args[i]));

			return internal_evaluate(expression_function->expression(), function_scope);
		}
		else {
			const auto* internal_function = dynamic_cast<const InternalFunction<T>*>(&find);
			if (internal_function)
				return internal_function->invoke(evaluated_args);
		}
	}

	throw std::runtime_error("Undefined node type for declaration calculator!");
}

}

#endif //EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_DECLARATIONS_CALCULATOR_HPP_
