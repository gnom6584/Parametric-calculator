#include <iostream>
#include <cmath>
#include <complex>
#include <cstring>

#include "expression_system/tree/function_invocation.hpp"
#include "expression_system/substituted_elements/internal_function.hpp"
#include "expression_system/tree/expression.hpp"
#include "expression_system/tree/number.hpp"
#include "expression_system/substituted_elements/expression_function.hpp"
#include "expression_system/calculator/declarations_stack.hpp"
#include "expression_system/tree/parameter.hpp"
#include "expression_system/calculator/declarations_calculator.hpp"
#include "expression_system/parser/string_parser.hpp"
#include "expression_system/utility/string_utility.hpp"
#include "expression_system/utility/transform_view.hpp"

#ifdef WASM
#include <emscripten/emscripten.h>
#endif
using T = std::complex<double>;

using namespace expression_system;
using namespace expression_system::parser;
using namespace expression_system::utility;
using namespace expression_system::tree;
using namespace expression_system::calculator;
using namespace expression_system::substituted_elements;


struct Add : public InternalFunction<T> {

	Add() : InternalFunction(2) {

	}

	T invoke(const std::vector<T>& args) const override {
		return args[0] + args[1];
	}
};

struct Sub : public InternalFunction<T> {

	Sub() : InternalFunction(2) {}

	T invoke(const std::vector<T>& args) const override {
		return args[0] - args[1];
	}
};

struct Mul : public InternalFunction<T> {

	Mul() : InternalFunction(2) {}

	T invoke(const std::vector<T>& args) const override {
		return args[0] * args[1];
	}
};

struct Div : public InternalFunction<T> {

	Div() : InternalFunction(2) {}

	T invoke(const std::vector<T>& args) const override {
		return args[0] / args[1];
	}
};

struct Pow : public InternalFunction<T> {

	Pow() : InternalFunction(2) {}

	T invoke(const std::vector<T>& args) const override {
		return std::pow(args[0], args[1]);
	}
};

struct Minus : public InternalFunction<T> {

	Minus() : InternalFunction(1) {}

	T invoke(const std::vector<T>& args) const override {
		return -args[0];
	}
};

struct Plus : public InternalFunction<T> {

	Plus() : InternalFunction(1) {}

	T invoke(const std::vector<T>& args) const override {
		return args[0];
	}
};

struct Fact : public InternalFunction<T> {

	Fact() : InternalFunction(1) {}

	int fact(int n) const {
		return (n==0) || (n==1) ? 1 : n* fact(n-1);
	}

	T invoke(const std::vector<T>& args) const override {
		return {(double)fact((int)(args[0].real())), args[0].imag()};
	}
};


struct Sin : public InternalFunction<T> {

	Sin() : InternalFunction(1) {}

	T invoke(const std::vector<T>& args) const override {
		return std::sin(args[0]);
	}
};

struct Cos : public InternalFunction<T> {

	Cos() : InternalFunction(1) {}

	T invoke(const std::vector<T>& args) const override {
		return std::cos(args[0]);
	}
};

struct Tan : public InternalFunction<T> {

	Tan() : InternalFunction(1) {}

	T invoke(const std::vector<T>& args) const override {
		return std::tan(args[0]);
	}
};

struct Atan : public InternalFunction<T> {

	Atan() : InternalFunction(1) {}

	T invoke(const std::vector<T>& args) const override {
		return std::atan(args[0]);
	}
};

struct Cotan : public InternalFunction<T> {

	Cotan() : InternalFunction(1) {}

	T invoke(const std::vector<T>& args) const override {
		return 1.0 / std::tan(args[0]);
	}
};




bool init = false;
extern "C" {

int
#ifdef WASM
EMSCRIPTEN_KEEPALIVE
#endif
free_str(char* ptr) {
	delete ptr;
	return 0;
}

bool is_number(const std::string& str) {
	using namespace std;
	auto dots_count = 0;
	if(str.starts_with('.'))
		return false;
	return all_of(begin(str), end(str), [&str, &dots_count](auto c) {
		if(c == '.')
			++dots_count;
		if(dots_count > 1)
			return false;
		return isdigit(c) || c == '.';
	});
}

StringParser<T> _parser([](auto str) {return std::stod(str);}, is_number);
DeclarationsCalculator<T> _calculator;

const char*
#ifdef WASM
EMSCRIPTEN_KEEPALIVE
#endif
run(const char* c_line) {
	std::string line(c_line);

#ifdef WASM
	{
		std::stringstream ss;
		ss << "console.log(\"" << line << "\");";
		emscripten_run_script(ss.str().c_str());
	}
#endif
	try {
		if(!init) {
			_calculator.declarations().declare_function("add", new Add());
			_calculator.declarations().declare_function("sub", new Sub());
			_calculator.declarations().declare_function("mul", new Mul());
			_calculator.declarations().declare_function("div", new Div());
			_calculator.declarations().declare_function("pow", new Pow());
			_calculator.declarations().declare_function("sin", new Sin());
			_calculator.declarations().declare_function("cos", new Cos());
			_calculator.declarations().declare_function("tg", new Tan());
			_calculator.declarations().declare_function("arctg", new Atan());
			_calculator.declarations().declare_function("ctg", new Cotan());
			_calculator.declarations().declare_function("positive", new Plus());
			_calculator.declarations().declare_function("negative", new Minus());
			_calculator.declarations().declare_function("fact", new Fact());

			_parser.add_unary_prefix_operator("-", "negative");
			_parser.add_unary_prefix_operator("+", "positive");
			_parser.add_unary_postfix_operator("!", "fact");
			_parser.add_binary_operator("+", "add", 0);
			_parser.add_binary_operator("-", "sub", 0);
			_parser.add_binary_operator("*", "mul", 1);
			_parser.add_binary_operator("/", "div", 1);
			_parser.add_binary_operator("^", "pow", 2);

			_calculator.declarations().declare_parameter("i", std::complex(0.0, 1.0));
			_calculator.declarations().declare_parameter("e", std::exp(1.0));
			_calculator.declarations().declare_parameter("pi", M_PI);
			init = true;
		}
		int l = 0;
		if ((l = line.find('=')) != std::string::npos) {
			std::string left = StringUtility::strip(line.substr(0, l));
			std::string right = line.substr(l + 1, std::size(line));
			int b = line.find('(');

			if (left.starts_with("binary")) {
				_parser.add_binary_operator(left.substr(6, std::size(left)), std::move(StringUtility::strip(right)), 10);
				return nullptr;
			}
			if (left.starts_with("unary_prefix")) {
				_parser.add_unary_prefix_operator(left.substr(12, std::size(left)), std::move(StringUtility::strip(right)));
				return nullptr;
			}
			if (left.starts_with("unary_postfix")) {
				_parser.add_unary_postfix_operator(left.substr(12, std::size(left)), std::move(StringUtility::strip(right)));
				return nullptr;
			}
			if (b == std::string::npos)
				_calculator.declarations().declare_parameter(left, _calculator.evaluate(*_parser.parse(right)));
			else {
				if (b == 0 || !left.ends_with(')'))
					throw std::runtime_error("Invalid function declaration!");

				std::string name;
				int i = 0;
				while (left[i] != '(') {
					name += left[i];
					++i;
				}
				++i;
				std::vector<std::string> parameters;
				while (left[i] != ')') {
					if (left[i] == ',')
						parameters.emplace_back();
					else {
						if (parameters.empty())
							parameters.emplace_back();
						parameters.back() += left[i];
					}
					++i;
				}
				_calculator.declarations().declare_function(name, new ExpressionFunction<T>(parameters, _parser.parse(right)));
			}

		}
		else {
			auto it = _calculator.evaluate(*_parser.parse(line));
			std::stringstream ss;
			ss << it.real() << std::showpos << it.imag();
			auto cppstr = ss.str();
			char * msg = new char[cppstr.length() + 1];
			for(int i=0;i<cppstr.length();i++) {
				msg[i]=cppstr[i];
			}
			msg[cppstr.length()] = '\0';
			return msg;
		}
	}
	catch (std::exception& ex) {
		std::string exm(ex.what());
		char* c = new char[exm.length() + 1];
		strcpy(c, exm.c_str());
		c[exm.length()] = '\0';
		return c;
	}
	return nullptr;
}
}
#ifndef WASM
int main() {

	while(true) {
		std::string line;
		std::getline(std::cin, line);
		auto c = run(line.c_str());

		if(c != nullptr) {
			std::cout << c << std::endl;
			delete c;
		}
	}
	return 0;
}
#endif
