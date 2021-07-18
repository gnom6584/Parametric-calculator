//
// Created by Name on 13.07.2021.
//

#ifndef EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_PARAMETER_HPP_
#define EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_PARAMETER_HPP_

#include <utility>

#include "../utility/named.hpp"
#include "expression.hpp"

namespace expression_system::tree {

template <typename T>
class Parameter final : public Expression<T>, public utility::Named {
public:
	explicit Parameter(utility::Named::ValueType name);
};


//////////////////////////////////////////////////////
//                  Implementation                  //
//////////////////////////////////////////////////////


template <typename T>
Parameter<T>::Parameter(utility::Named::ValueType name)
	: Named(std::forward<utility::Named::ValueType>(name)) {}

}
#endif //EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_PARAMETER_HPP_
