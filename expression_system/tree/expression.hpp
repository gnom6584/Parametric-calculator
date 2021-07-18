//
// Created by Name on 13.07.2021.
//

#ifndef EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_EXPRESSION_HPP_
#define EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_EXPRESSION_HPP_


namespace expression_system::tree {

template <typename T>
class Expression {
public:
	Expression() = default;

	Expression(const Expression& expression) = delete;

	Expression& operator=(const Expression& expression) = delete;

	virtual ~Expression() = default;
};

}
#endif //EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_EXPRESSION_HPP_
