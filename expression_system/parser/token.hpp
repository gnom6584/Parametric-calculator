//
// Created by Name on 17.07.2021.
//

#ifndef EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_PARSER_TOKEN_HPP_
#define EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_PARSER_TOKEN_HPP_

#include <vector>
#include <string>
#include <set>

namespace expression_system::parser {

class Token {
public:

	Token(std::string str, size_t position);

	[[nodiscard]] size_t position() const;

	bool operator==(const std::string& str) const;

	bool operator==(const char* c_str) const;

	void push_back(char c);

	[[nodiscard]] const std::string& str() const;

	void strip();

private:
	std::string _str;

	size_t _position;
};


std::vector<Token> tokenize(const std::string& str, const std::set<std::string>& separators);

}
#endif //EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_PARSER_TOKEN_HPP_
