//
// Created by Name on 14.07.2021.
//

#ifndef EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_EXPRESSION_FUNCTION_HPP_
#define EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_EXPRESSION_FUNCTION_HPP_

#include <utility>
#include <vector>
#include <string>
#include <map>

#include "function.hpp"
#include "../tree/expression.hpp"

namespace expression_system::substituted_elements {

template <typename T>
class ExpressionFunction final : public Function<T> {
public:

	explicit ExpressionFunction(std::vector<std::string> parameters, tree::Expression<T>* expression);

	[[nodiscard]] size_t arguments_count() const override;

	[[nodiscard]] const std::string& get_parameter(size_t index) const;

	const tree::Expression<T>& expression() const;

	~ExpressionFunction() override;

private:

	tree::Expression<T>* _expression;

	const std::vector<std::string> _parameters;

	friend tree::Expression<T>;
};


//////////////////////////////////////////////////////
//                  Implementation                  //
//////////////////////////////////////////////////////


template <typename T>
ExpressionFunction<T>::ExpressionFunction(std::vector<std::string> parameters, tree::Expression<T>* expression)
	: _expression(expression), _parameters(std::move(parameters)) {}


template <typename T>
size_t ExpressionFunction<T>::arguments_count() const {
	return std::size(_parameters);
}


template <typename T>
const std::string& ExpressionFunction<T>::get_parameter(size_t index) const {
	return _parameters[index];
}


template <typename T>
const tree::Expression<T>& ExpressionFunction<T>::expression() const {
	return *_expression;
}


template <typename T>
ExpressionFunction<T>::~ExpressionFunction() {
	delete _expression;
}

}
#endif //EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_EXPRESSION_FUNCTION_HPP_
