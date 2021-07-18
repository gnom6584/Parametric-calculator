//
// Created by Name on 17.07.2021.
//

#ifndef EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_PARSER_TREE_FUNCTION_INVOCATION_UNIT_HPP_
#define EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_PARSER_TREE_FUNCTION_INVOCATION_UNIT_HPP_

#include "parse_unit.hpp"
#include "../../tree/function_invocation.hpp"

#include <vector>
#include <string>
#include <memory>

namespace expression_system::parser::tree {

template <typename T>
class FunctionInvocationUnit : public ParseUnit<T> {
public:

	FunctionInvocationUnit(const std::string& name, std::vector<ParseUnit<T>*> args);

	virtual expression_system::tree::Expression<T>* evaluate(const StringParser<T>& string_parser);

private:
	const std::string& _name;
	std::vector<ParseUnit<T>*> _args;
};


//////////////////////////////////////////////////////
//                  Implementation                  //
//////////////////////////////////////////////////////


template <typename T>
FunctionInvocationUnit<T>::FunctionInvocationUnit(const std::string& name, std::vector<ParseUnit<T>*> args)
	: _name(name), _args(std::move(args)) {}


template <typename T>
expression_system::tree::Expression<T>* FunctionInvocationUnit<T>::evaluate(const StringParser<T>& string_parser) {

	auto casted = std::vector<expression_system::tree::Expression<T>*>();
	casted.reserve(std::size(_args));

	for (int i = 0; i < std::size(_args); ++i) {
		casted.emplace_back(_args[i]->evaluate(string_parser));
		delete _args[i];
	}

	return new expression_system::tree::FunctionInvocation(std::make_shared<std::string>(_name), std::move(casted));
}

}

#endif //EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_PARSER_TREE_FUNCTION_INVOCATION_UNIT_HPP_
