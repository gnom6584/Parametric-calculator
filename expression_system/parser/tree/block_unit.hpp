//
// Created by Name on 17.07.2021.
//

#ifndef EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_PARSER_TREE_BLOCK_UNIT_HPP_
#define EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_PARSER_TREE_BLOCK_UNIT_HPP_

#include "parse_unit.hpp"
#include "expression_unit.hpp"
#include "operator_unit.hpp"
#include "number_unit.hpp"
#include <list>

namespace expression_system::parser::tree {

template <typename T>
class BlockUnit : public ParseUnit<T> {
public:

	expression_system::tree::Expression<T>* evaluate(const StringParser<T>& string_parser) override;

	void take_unit(ParseUnit<T>* unit);
#ifndef NDEBUG
	std::string dump();
#endif
	~BlockUnit() override;
private:

	std::list<ParseUnit<T>*> _children;
};

//////////////////////////////////////////////////////
//                  Implementation                  //
//////////////////////////////////////////////////////


template <typename T>
expression_system::tree::Expression<T>* BlockUnit<T>::evaluate(const StringParser<T>& string_parser) {

	if(_children.size() == 0)
		throw std::runtime_error("Empty expression!");

	auto header = begin(_children);


	while (header != end(_children)) {
		if (dynamic_cast<BlockUnit<T>*>(*header)) {
			auto evaluate_block_result = (*header)->evaluate(string_parser);
			delete *header;
			header = _children.erase(header);
			header = _children.insert(header, new ExpressionUnit(evaluate_block_result));
		}
		header++;
	}

	header = end(_children);
	--header;
	while (header != end(_children)) {

		auto as_operator = dynamic_cast<OperatorUnit<T>*>(*header);
		if (as_operator && as_operator->type() == OperatorUnit<T>::Type::UnaryPrefix) {
			for (const auto&[sign, alias] : string_parser._unary_prefix_operators) {
				if (sign == as_operator->sign()) {
					auto right = next(header);

					if(right == std::end(_children))
						throw std::runtime_error("Evaluate unary prefix operator error");

					auto right_as_operator = dynamic_cast<OperatorUnit<T>*>(*right);
					if(right_as_operator)
						if(right_as_operator->type() != OperatorUnit<T>::Type::UnaryPrefix)
							throw std::runtime_error("Evaluate unary prefix operator error");

					auto right_value = (*right)->evaluate(string_parser);
					auto new_unit = new expression_system::tree::FunctionInvocation<T>(std::make_shared<std::string>(alias), {right_value});

					delete *header;
					header = _children.erase(header);
					delete *header;
					header = _children.erase(header);
					header = _children.insert(header, new ExpressionUnit(new_unit));
				}
			}
		}
		--header;
	}


	header = begin(_children);
	while (header != end(_children)) {

		auto as_operator = dynamic_cast<OperatorUnit<T>*>(*header);
		if (as_operator && as_operator->type() == OperatorUnit<T>::Type::UnaryPostfix) {
			for (const auto&[sign, alias] : string_parser._unary_postfix_operators) {
				if (sign == as_operator->sign()) {
					auto left = prev(header);

					if(left == std::end(_children))
						throw std::runtime_error("Evaluate unary postfix operator error");

					auto left_as_operator = dynamic_cast<OperatorUnit<T>*>(*left);
					if(left_as_operator)
						if(left_as_operator->type() != OperatorUnit<T>::Type::UnaryPostfix)
							throw std::runtime_error("Evaluate unary postfix operator error");

					auto left_value = (*left)->evaluate(string_parser);
					auto new_unit = new expression_system::tree::FunctionInvocation<T>(std::make_shared<std::string>(alias), {left_value});

					delete *left;
					header = _children.erase(left);
					delete *header;
					header = _children.erase(header);
					header = _children.insert(header, new ExpressionUnit(new_unit));
				}
			}
		}
		++header;
	}

	for (const auto&[_, operators] : string_parser._binary_operators_by_precedence) {
		header = begin(_children);
		while (header != end(_children)) {
			auto as_operator = dynamic_cast<OperatorUnit<T>*>(*header);
			if (as_operator && as_operator->type() == OperatorUnit<T>::Type::Binary) {
				auto left = prev(header);
				auto right = next(header);

				if(left == end(_children) || right == end(_children))
					throw std::runtime_error("Evaluate binary operator error");

				auto left_as_operator = dynamic_cast<OperatorUnit<T>*>(*left);

				if(left_as_operator && left_as_operator->type() != OperatorUnit<T>::Type::UnaryPostfix)
					throw std::runtime_error("Evaluate binary operator error");

				auto right_as_operator = dynamic_cast<OperatorUnit<T>*>(*right);

				if(right_as_operator && right_as_operator->type() == OperatorUnit<T>::Type::UnaryPrefix)
					throw std::runtime_error("Evaluate binary operator error");

				for (const auto&[sign, alias] : operators) {
					if (sign == as_operator->sign()) {
						auto left_value = (*left)->evaluate(string_parser);
						auto right_value = (*right)->evaluate(string_parser);
						auto new_unit = new expression_system::tree::FunctionInvocation<T>(std::make_shared<std::string>(alias), {left_value, right_value});
						delete *left;
						header = _children.erase(left);
						delete *header;
						header = _children.erase(header);
						delete *header;
						header = _children.erase(header);
						header = _children.insert(header, new ExpressionUnit(new_unit));
					}
					else
						++header;
				}
			}
			else
				++header;
		}
	}

	auto eval = _children.back()->evaluate(string_parser);
	return eval;
}


template <typename T>
void BlockUnit<T>::take_unit(ParseUnit<T>* unit) {
	_children.emplace_back(unit);
}


template <typename T>
BlockUnit<T>::~BlockUnit() {

	for (auto it : _children)
		delete it;
}

#ifndef NDEBUG
template <typename T>
std::string BlockUnit<T>::dump() {
	auto str = std::string();
	for(auto child : _children) {

		const auto& typeid_to_human = [](std::string str) {
			str.pop_back();
			str.pop_back();
			str.pop_back();
			str.pop_back();
			str.erase(0, std::string("N17expression_system6parser4tree9").length());
			return str;
		};

		str += typeid_to_human(typeid(*child).name());
		if(dynamic_cast<OperatorUnit<T>*>(child)) {
			str += "(" + std::to_string((int)dynamic_cast<OperatorUnit<T>*>(child)->type()) + ")";
		}
		str += ", ";
	}
	return str;
}
#endif
}

#endif //EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_PARSER_TREE_BLOCK_UNIT_HPP_
