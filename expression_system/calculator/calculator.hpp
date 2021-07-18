//
// Created by Name on 14.07.2021.
//

#ifndef EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_CALCULATOR_HPP_
#define EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_CALCULATOR_HPP_

#include "../tree/expression.hpp"

namespace expression_system::calculator {

template <typename T>
class Calculator {
public:
	[[nodiscard]] virtual T evaluate(const tree::Expression<T>& expression) const = 0;
};

}
#endif //EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_CALCULATOR_HPP_
