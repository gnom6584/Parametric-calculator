//
// Created by Name on 13.07.2021.
//

#ifndef EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_NUMBER_HPP_
#define EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_NUMBER_HPP_

#include <utility>

#include "expression.hpp"

namespace expression_system::tree {

template <typename T>
class Number final : public Expression<T> {
public:

	explicit Number(T value);

	Number(Number&&) noexcept;

	Number& operator=(Number&&) noexcept;

	const T& value() const;

private:

	T _value;
};


//////////////////////////////////////////////////////
//                  Implementation                  //
//////////////////////////////////////////////////////


template <typename T>
Number<T>::Number(T value)
	: _value(std::forward<T>(value)) {}


template <typename T>
Number<T>::Number(Number&& rvalue) noexcept
	: _value(std::forward<T>(rvalue._value)) {}


template <typename T>
Number<T>& Number<T>::operator=(Number&& rvalue) noexcept {
	_value = std::forward<T>(rvalue._value);
	return *this;
}


template <typename T>
const T& Number<T>::value() const {
	return _value;
}

}

#endif //EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_NUMBER_HPP_
