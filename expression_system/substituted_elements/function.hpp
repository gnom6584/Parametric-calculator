//
// Created by Name on 14.07.2021.
//

#ifndef EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_FUNCTION_HPP_
#define EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_FUNCTION_HPP_

#include <vector>

#include "../tree/expression.hpp"

namespace expression_system::substituted_elements {

template <typename T>
class Function {
public:

	[[nodiscard]] virtual size_t arguments_count() const = 0;

	virtual ~Function() = default;
};

}
#endif //EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_FUNCTION_HPP_