//
// Created by Name on 17.07.2021.
//

#ifndef EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_PARSER_TREE_OPERATOR_UNIT_HPP_
#define EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_PARSER_TREE_OPERATOR_UNIT_HPP_

#include "parse_unit.hpp"

#include <memory>
#include <string>
#include <utility>

namespace expression_system::parser::tree {

template <typename T>
class OperatorUnit : public ParseUnit <T>{
public:

	enum class Type {
		UnaryPrefix,
		UnaryPostfix,
		Binary
	};

	OperatorUnit(std::string sign, Type type, size_t precedence = 0);

	[[nodiscard]] const std::string& sign() const;

	[[nodiscard]] size_t precedence() const;

	[[nodiscard]] Type type() const;

	//В РОТ ЕБАЛ НАХУЙ БЛЯДЬ АЫВРОФПАРО ФЫРЛДАОФЫЖДЭЛ АРОЛДЫФ АРЛОФЫРАЛДО
	expression_system::tree::Expression<T>* evaluate(const StringParser<T>& string_parser) override;

private:
	std::string _sign;

	size_t _precedence;

	Type _type;
};


//////////////////////////////////////////////////////
//                  Implementation                  //
//////////////////////////////////////////////////////


template <typename T>
typename OperatorUnit<T>::Type OperatorUnit<T>::type() const {
	return _type;
}


template <typename T>
size_t OperatorUnit<T>::precedence() const {
	return _precedence;
}


template <typename T>
const std::string& OperatorUnit<T>::sign() const {
	return _sign;
}


template <typename T>
OperatorUnit<T>::OperatorUnit(std::string sign, OperatorUnit::Type type, size_t precedence)
	: _sign(std::move(sign)), _precedence(precedence), _type(type) {}


template <typename T>
expression_system::tree::Expression<T>* OperatorUnit<T>::evaluate(const StringParser<T>& string_parser) {
	 throw std::runtime_error("ЧЕ ЗА НАХУЙ?" + _sign + std::to_string((int)type()));
}

}

#endif //EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_PARSER_TREE_OPERATOR_UNIT_HPP_
