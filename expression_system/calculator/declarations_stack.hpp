//
// Created by Name on 14.07.2021.
//

#ifndef EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_DECLARATIONS_STACK_HPP_
#define EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_DECLARATIONS_STACK_HPP_

#include <string>
#include <map>
#include <set>
#include <vector>
#include <memory>
#include "../substituted_elements/function.hpp"

namespace expression_system::calculator {

template <typename T>
class DeclarationsContainer final {
public:

	DeclarationsContainer();

	DeclarationsContainer(const DeclarationsContainer&) = delete;

	DeclarationsContainer& operator=(const DeclarationsContainer&) = delete;

	DeclarationsContainer push() const;

	DeclarationsContainer& declare_parameter(std::string parameter_name, T number);

	DeclarationsContainer& declare_function(std::string function_name, substituted_elements::Function<T>* function);

	const T& get_parameter(const std::string& name) const;

	const substituted_elements::Function<T>& get_function(const std::string& name, size_t arguments_count) const;

	~DeclarationsContainer();

private:

	std::map<std::string, std::map<int, substituted_elements::Function<T>*>> _functions;

	std::map<std::string, T> _parameters;

	const DeclarationsContainer* _parent;

	explicit DeclarationsContainer(const DeclarationsContainer* parent);
};

//////////////////////////////////////////////////////
//                  Implementation                  //
//////////////////////////////////////////////////////


template <typename T>
DeclarationsContainer<T>::DeclarationsContainer()
	: _parent(nullptr) {}


template <typename T>
DeclarationsContainer<T>::DeclarationsContainer(const DeclarationsContainer* parent)
	: _parent(parent) {}


template <typename T>
DeclarationsContainer<T> DeclarationsContainer<T>::push() const {
	return DeclarationsContainer(this);
}


template <typename T>
DeclarationsContainer<T>& DeclarationsContainer<T>::declare_parameter(std::string parameter_name, T number) {
	using namespace std;

	if(_parameters.find(parameter_name) == std::end(_parameters))
		_parameters.emplace(std::move(parameter_name), std::move(number));
	else
		throw std::runtime_error("Redefinition of parameter: " + parameter_name);

	return *this;
}


template <typename T>
DeclarationsContainer<T>& DeclarationsContainer<T>::declare_function(std::string function_name, substituted_elements::Function<T>* function) {
	auto iterator = _functions.find(function_name);
	if(iterator == std::end(_functions))
		_functions.emplace(std::move(function_name), std::map<int, substituted_elements::Function<T>*>({{function->arguments_count(), std::move(function)}}));
	else if(iterator->second.find(function->arguments_count()) == std::end(iterator->second))
		iterator->second.emplace(function->arguments_count(), std::move(function));
	else
		throw std::runtime_error("Redefinition of function: " + function_name + " of arity = " + std::to_string(function->arguments_count()));
	return *this;
}


template <typename T>
const T& DeclarationsContainer<T>::get_parameter(const std::string& name) const {
	using namespace std;
	auto find_it = _parameters.find(name);
	if(find_it != end(_parameters))
		return find_it->second;
	else if(_parent != nullptr)
		return _parent->get_parameter(name);
	throw std::runtime_error("Parameter: " + name + " not found");
}


template <typename T>
const substituted_elements::Function<T>& DeclarationsContainer<T>::get_function(const std::string& name, size_t arguments_count) const {
	using namespace std;
	const auto& find_function_array = _functions.find(name);

	if(find_function_array != end(_functions) && find_function_array->second.find(arguments_count) != end(find_function_array->second))
		return *find_function_array->second.find(arguments_count)->second;
	else if(_parent != nullptr)
		return _parent->get_function(name, arguments_count);

	throw std::runtime_error("Function: " + name + " of arity = " + to_string(arguments_count) + " not found");
}


template <typename T>
DeclarationsContainer<T>::~DeclarationsContainer() {
	for(auto&[_, functions_pointers] : _functions)
		for(auto&[_, function_pointer] : functions_pointers)
			delete function_pointer;
}

}
#endif //EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_DECLARATIONS_STACK_HPP_