//
// Created by Name on 17.07.2021.
//

#ifndef EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_TREE_PARSE_UNIT_HPP_
#define EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_TREE_PARSE_UNIT_HPP_

#include "../../tree/expression.hpp"

namespace expression_system::parser {
	template <typename T>
	class StringParser;
}

namespace expression_system::parser::tree {

template <typename T>
class ParseUnit {
public:
	virtual expression_system::tree::Expression<T>* evaluate(const StringParser<T>& string_parser) = 0;

	virtual ~ParseUnit() = default;
};

}

#endif //EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_TREE_PARSE_UNIT_HPP_
