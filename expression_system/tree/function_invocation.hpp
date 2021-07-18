//
// Created by Name on 13.07.2021.
//

#ifndef EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_FUNCTION_INVOCATION_HPP_
#define EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_FUNCTION_INVOCATION_HPP_

#include <string>
#include <vector>

#include "../utility/named.hpp"
#include "expression.hpp"

namespace expression_system::tree {

template <typename T>
class FunctionInvocation final : public Expression<T>, public utility::Named {
public:

	explicit FunctionInvocation(utility::Named::ValueType name, std::vector<Expression<T>*> arguments);

	[[nodiscard]] size_t arguments_count() const;

	const Expression<T>& operator[](size_t index) const;

	FunctionInvocation(const FunctionInvocation& function_invocation) = delete;

	FunctionInvocation& operator=(const FunctionInvocation& function_invocation) = delete;

	~FunctionInvocation<T>() override;

private:
	std::vector<Expression<T>*> _arguments;
};


//////////////////////////////////////////////////////
//                  Implementation                  //
//////////////////////////////////////////////////////


template <typename T>
FunctionInvocation<T>::FunctionInvocation(utility::Named::ValueType name, std::vector<Expression<T>*> arguments)
	: Named(std::forward<utility::Named::ValueType>(name)), _arguments(std::move(arguments)) {}

template <typename T>
size_t FunctionInvocation<T>::arguments_count() const {
	return std::size(_arguments);
}

template <typename T>
const Expression<T>& FunctionInvocation<T>::operator[](size_t index) const {
	return *_arguments[index];
}


template <typename T>
FunctionInvocation<T>::~FunctionInvocation<T>() {
	for(auto arg : _arguments)
		delete arg;
}

}
#endif //EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_FUNCTION_INVOCATION_HPP_
