//
// Created by Name on 14.07.2021.
//

#include "named.hpp"

using namespace expression_system::utility;

Named::Named(ValueType name) : _name(std::forward<ValueType>(name)) {}

const std::string & Named::name() const {
	return *_name;
}