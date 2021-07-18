//
// Created by Name on 15.07.2021.
//

#ifndef EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_UTILITY_STRING_UTILITY_HPP_
#define EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_UTILITY_STRING_UTILITY_HPP_

#include <vector>
#include <set>
#include <string>

namespace expression_system::utility {

class StringUtility {
public:
	static std::vector<std::string> split_keep_by_strings(const std::string& str, const std::set<std::string>& separators);

	static std::string strip(const std::string& str);
};

}

#endif //EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_UTILITY_STRING_UTILITY_HPP_
