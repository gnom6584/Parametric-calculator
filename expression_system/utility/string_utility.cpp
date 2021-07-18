//
// Created by Name on 15.07.2021.
//

#include "string_utility.hpp"

using namespace expression_system::utility;
using namespace std;

vector<string> StringUtility::split_keep_by_strings(const std::string& str, const set<string>& separators) {
	vector<string> result;

	bool last_was_operator = false;
	for (size_t i = 0; i < str.length();) {
		bool cont = false;
		for(auto it = rbegin(separators); it != rend(separators); ++it) {
			if(str.find(*it, i) == i) {
				cont = true;
				result.emplace_back(*it);
				i += it->length();
				last_was_operator = true;
				break;
			}
		}
		if(cont)
			continue;
		if(last_was_operator || result.empty()) {
			result.emplace_back();
			last_was_operator = false;
		}
		result.back().push_back(str[i]);
		++i;
	}

	return result;
}


string StringUtility::strip(const string& str) {
	string result;

	const static std::string skip = " \n\t";

	for (char c : str) {
		if (count(begin(skip), end(skip), c))
			continue;
		result.push_back(c);
	}

	return result;
}
