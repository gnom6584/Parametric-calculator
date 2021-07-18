//
// Created by Name on 17.07.2021.
//

#ifndef EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_PARSER_TREE_NUMBER_UNIT_HPP_
#define EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_PARSER_TREE_NUMBER_UNIT_HPP_

#include "parse_unit.hpp"
#include "../../tree/number.hpp"

namespace expression_system::parser::tree {

template <typename T>
class NumberUnit : public ParseUnit<T> {
public:
	explicit NumberUnit(T&& value);

	expression_system::tree::Expression<T>* evaluate(const StringParser<T>& string_parser) override;

private:
	T _value;
};


//////////////////////////////////////////////////////
//                  Implementation                  //
//////////////////////////////////////////////////////


template <typename T>
NumberUnit<T>::NumberUnit(T&& value)
	: _value(value) {}


template <typename T>
expression_system::tree::Expression<T>* NumberUnit<T>::evaluate(const StringParser<T>& string_parser) {
	return new expression_system::tree::Number<T>(std::forward<T>(_value));
}

}

#endif //EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_PARSER_TREE_NUMBER_UNIT_HPP_
