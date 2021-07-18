//
// Created by Name on 17.07.2021.
//

#ifndef EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_PARSER_TREE_PARAMETER_UNIT_HPP_
#define EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_PARSER_TREE_PARAMETER_UNIT_HPP_

#include "parse_unit.hpp"
#include <string>
#include <memory>
#include <utility>

#include "../../tree/parameter.hpp"

namespace expression_system::parser::tree {

template <typename T>
class ParameterUnit : public ParseUnit<T> {
public:

	explicit ParameterUnit(const std::string& name);

	expression_system::tree::Expression<T>* evaluate(const StringParser<T>& string_parser) override;

private:
	const std::string& _name;
};


//////////////////////////////////////////////////////
//                  Implementation                  //
//////////////////////////////////////////////////////


template <typename T>
ParameterUnit<T>::ParameterUnit(const std::string& name) : _name(name) {}


template <typename T>
expression_system::tree::Expression<T>* ParameterUnit<T>::evaluate(const StringParser<T>& string_parser) {
	return new expression_system::tree::Parameter<T>(std::make_shared<std::string>(_name));
}

}
#endif //EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_PARSER_TREE_PARAMETER_UNIT_HPP_
