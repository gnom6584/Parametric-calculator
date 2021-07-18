//
// Created by Name on 14.07.2021.
//

#ifndef EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_PARSER_STRING_PARSER_HPP_
#define EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_PARSER_STRING_PARSER_HPP_

#include <functional>
#include <utility>
#include <set>
#include <list>

#include "../tree/expression.hpp"
#include "../utility/slice_view.hpp"
#include "../utility/transform_view.hpp"
#include "../utility/string_utility.hpp"

#include "tree/block_unit.hpp"
#include "tree/number_unit.hpp"
#include "tree/parameter_unit.hpp"
#include "tree/function_invocation_unit.hpp"
#include "tree/operator_unit.hpp"
#include "token.hpp"


//////////////////////////////////////////////////////
//                  АДСКИЙ  ПИЗДЕЦ                  //
//////////////////////////////////////////////////////

namespace expression_system::parser {

template <typename T>
class StringParser final {
public:

	StringParser(std::function<T(const std::string&)>&& string_to_number, std::function<bool(const std::string&)>&& is_number);

	[[nodiscard]] expression_system::tree::Expression<T>* parse(const std::string& string) const;

	StringParser& add_unary_prefix_operator(std::string&& sign, std::string&& function_alias);

	StringParser& add_unary_postfix_operator(std::string&& sign, std::string&& function_alias);

	StringParser& add_binary_operator(std::string&& sign, std::string&& function_alias, int precedence);

private:

	[[nodiscard]] tree::BlockUnit<T>* parse_block(const std::vector<Token>& tokens, size_t begin_index, size_t end_index, int depth = 0) const;

	[[nodiscard]] tree::FunctionInvocationUnit<T>* parse_function_invocation(const std::string& name,  const std::vector<Token>& tokens, size_t begin_index, size_t end_index, int depth) const;

	std::map<std::string, std::string> _unary_prefix_operators;

	std::map<std::string, std::string> _unary_postfix_operators;

	std::map<std::string, std::pair<int, std::string>> _binary_operators_by_sign;

	std::map<int, std::map<std::string, std::string>, std::greater<>> _binary_operators_by_precedence;

	std::function<T(const std::string&)> string_to_number;

	std::function<bool(const std::string&)> is_number;

	friend tree::BlockUnit<T>;
};


//////////////////////////////////////////////////////
//                  Implementation                  //
//////////////////////////////////////////////////////


template <typename T>
StringParser<T>::StringParser(std::function<T(const std::string&)>&& string_to_number, std::function<bool(const std::string&)>&& is_number)
	: string_to_number(string_to_number), is_number(is_number) {}


template <typename T>
StringParser<T>& StringParser<T>::add_unary_prefix_operator(std::string&& sign, std::string&& function_alias) {
	_unary_prefix_operators.emplace(sign, function_alias);
	return *this;
}


template <typename T>
StringParser<T>& StringParser<T>::add_unary_postfix_operator(std::string&& sign, std::string&& function_alias) {
	_unary_postfix_operators.emplace(sign, function_alias);
	return *this;
}


template <typename T>
StringParser<T>& StringParser<T>::add_binary_operator(std::string&& sign, std::string&& function_alias, int precedence) {
	auto copy = sign;
	_binary_operators_by_sign[sign] = std::make_pair(precedence, function_alias);
	_binary_operators_by_precedence[precedence][sign] = function_alias;
	return *this;
}


template <typename T>
expression_system::tree::Expression<T>* StringParser<T>::parse(const std::string& string) const {
	using namespace utility;
	using namespace std;

	std::set<std::string> separators;

	for(const auto& it : _unary_prefix_operators)
		separators.emplace(it.first);

	for(const auto& it : _unary_postfix_operators)
		separators.emplace(it.first);

	for(const auto& it : _binary_operators_by_sign)
		separators.emplace(it.first);

	separators.emplace("(");
	separators.emplace(")");
	separators.emplace(",");

	std::vector<Token> tokens = tokenize(string, separators);

	for(auto& token : tokens) {
		token.strip();
	}

	tokens.erase(remove_if(begin(tokens), end(tokens), [](auto& it) {
		return it.str().length() == 0;
	}), end(tokens));

	auto block = parse_block(tokens, 0, std::size(tokens));

	auto expr = block->evaluate(*this);
	delete block;
	return expr;

}

template <typename T>
tree::BlockUnit<T>* StringParser<T>::parse_block(const std::vector<Token>& tokens, size_t begin_index, size_t end_index, int dp) const {
	using namespace std;
	using namespace tree;
	using namespace expression_system::utility;
	long child_block_begin = 0;

	auto block = new BlockUnit<T>();

	int depth = 0;

	bool can_unary_prefix = true;
	for(auto i = begin_index; i < end_index; ++i) {
		const auto& token = tokens[i];

		if(token == "(") {
			if(depth == 0)
				child_block_begin = (long)i + 1;
			++depth;
			can_unary_prefix = true;
		}
		else if(token == ")") {
			--depth;
			if(depth == 0) {
				size_t child_block_end = i;
				auto ptr = parse_block(tokens, child_block_begin, child_block_end, dp + 1);
				block->take_unit(ptr);
			}
			can_unary_prefix = false;
		}
		else if(depth == 0) {

			auto is_unary_prefix_operator_it = _unary_prefix_operators.find(token.str());
			auto is_unary_postfix_operator_it = _unary_postfix_operators.find(token.str());
			auto is_binary_operator_it = _binary_operators_by_sign.find(token.str());

			if(is_binary_operator_it != end(_binary_operators_by_sign)
				|| is_unary_postfix_operator_it != end(_unary_postfix_operators)
					||  is_unary_prefix_operator_it != end(_unary_prefix_operators)) {
				if(can_unary_prefix) {
					if(is_unary_prefix_operator_it != end(_unary_prefix_operators)) {
						block->take_unit(new OperatorUnit<T>(token.str(), OperatorUnit<T>::Type::UnaryPrefix));
						can_unary_prefix = true;
					}
					else
						throw runtime_error("invalid operator: " + std::to_string(token.position()));
				}
				else {
					if (is_binary_operator_it != end(_binary_operators_by_sign)) {

						block->take_unit(new OperatorUnit<T>(token.str(), OperatorUnit<T>::Type::Binary, is_binary_operator_it->second.first));
						can_unary_prefix = true;
					}
					else if(is_unary_postfix_operator_it != end(_unary_postfix_operators)) {
						block->take_unit(new OperatorUnit<T>(token.str(), OperatorUnit<T>::Type::UnaryPostfix));
						can_unary_prefix = false;
					}
					else
						throw runtime_error("invalid operator: " + std::to_string(token.position()));
				}
			}
			else {
				if(is_number(token.str())) {
					block->take_unit(new NumberUnit<T>(string_to_number(token.str())));
				}
				else if(i < end_index - 1 && tokens[i + 1] == "(") {
					int d = 0;
					++i;
					++i;
					auto start = i;
					while (i < end_index) {
						if(tokens[i] == "(")
							d++;
						else if(tokens[i] == ")"){
							if(d == 0) {
								block->take_unit(parse_function_invocation(token.str(), tokens, start, i, dp + 1));
								break;
							}
							d--;
						}
						++i;
					}
					if(i == end_index)
						throw runtime_error("Unclosed brackets_");
				}
				else
					block->take_unit(new ParameterUnit<T>(token.str()));
				can_unary_prefix = false;
			}
		}
	}

	if(depth != 0)
		throw runtime_error("Unclosed brackets__" + std::to_string(dp));
	return block;
}


template <typename T>
tree::FunctionInvocationUnit<T>* StringParser<T>::parse_function_invocation(const std::string& name, const std::vector<Token>& tokens, size_t begin_index, size_t end_index, int depth) const {
	using namespace std;
	using namespace tree;
	using namespace expression_system::utility;
	size_t s = begin_index;
	std::vector<ParseUnit<T>*> args;
	for(size_t i = begin_index; i < end_index; ++i) {
		if(tokens[i] == ",") {
			args.emplace_back(parse_block(tokens, s, i, depth + 1));
			s = i + 1;
		}
	}
	args.emplace_back(parse_block(tokens, s, end_index, depth + 1));
	return new FunctionInvocationUnit<T>(name, args);
}

}
#endif //EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_PARSER_STRING_PARSER_HPP_
