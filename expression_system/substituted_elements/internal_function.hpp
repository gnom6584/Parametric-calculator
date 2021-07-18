//
// Created by Name on 13.07.2021.
//

#ifndef EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_INTERNAL_FUNCTION_HPP_
#define EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_INTERNAL_FUNCTION_HPP_

#include <vector>

#include "function.hpp"

namespace expression_system::substituted_elements {


template <typename T>
class InternalFunction : public Function<T> {
public:

	explicit InternalFunction(size_t arguments_count);

	[[nodiscard]] size_t arguments_count() const override;

	[[nodiscard]] virtual T invoke(const std::vector<T>& args) const = 0;

private:
	const size_t _arguments_count;
};


//////////////////////////////////////////////////////
//                  Implementation                  //
//////////////////////////////////////////////////////


template <typename T>
InternalFunction<T>::InternalFunction(size_t arguments_count)
	: _arguments_count(arguments_count) {}


template <typename T>
size_t InternalFunction<T>::arguments_count() const {
	return _arguments_count;
}

}
#endif //EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_INTERNAL_FUNCTION_HPP_
