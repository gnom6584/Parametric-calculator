//
// Created by Name on 17.07.2021.
//

#ifndef EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_PARSER_TREE_EXPRESSION_UNIT_HPP_
#define EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_PARSER_TREE_EXPRESSION_UNIT_HPP_

#include "parse_unit.hpp"

#include "../../tree/expression.hpp"

namespace expression_system::parser::tree {

template <typename T>
class ExpressionUnit : public ParseUnit<T> {
public:
	explicit ExpressionUnit(expression_system::tree::Expression<T>* value);

	expression_system::tree::Expression<T>* evaluate(const StringParser<T>& string_parser) override;

private:
	expression_system::tree::Expression<T>* _value;
};


//////////////////////////////////////////////////////
//                  Implementation                  //
//////////////////////////////////////////////////////


template <typename T>
ExpressionUnit<T>::ExpressionUnit(expression_system::tree::Expression<T>* value) : _value(value) {

}


template <typename T>
expression_system::tree::Expression<T>* ExpressionUnit<T>::evaluate(const StringParser<T>& string_parser) {
	return _value;
}

}
#endif //EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_PARSER_TREE_EXPRESSION_UNIT_HPP_
