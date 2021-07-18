//
// Created by Name on 17.07.2021.
//

#include "token.hpp"
#include "../utility/string_utility.hpp"

namespace expression_system::parser {

Token::Token(std::string str, size_t position) : _str(std::move(str)), _position(position) {

}


size_t Token::position() const {
	return _position;
}


bool Token::operator==(const std::string& str) const {
	return _str == str;
}


bool Token::operator==(const char* c_str) const {
	return _str == c_str;
}


void Token::push_back(char c) {
	_str.push_back(c);
}


void Token::strip() {
	_str = utility::StringUtility::strip(_str);
}


const std::string& Token::str() const {
	return _str;
}


std::vector<Token> tokenize(const std::string& str, const std::set<std::string>& separators) {
	std::vector<Token> result;

	bool last_was_operator = false;
	for (size_t i = 0; i < str.length();) {
		bool cont = false;
		for (auto it = rbegin(separators); it != rend(separators); ++it) {
			if (str.find(*it, i) == i) {
				cont = true;
				result.emplace_back(*it, i);
				i += it->length();
				last_was_operator = true;
				break;
			}
		}
		if (cont)
			continue;
		if (last_was_operator || result.empty()) {
			result.emplace_back("", i);
			last_was_operator = false;
		}
		result.back().push_back(str[i]);
		++i;
	}

	return result;
}
}