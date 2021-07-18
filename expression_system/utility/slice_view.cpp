//
// Created by Name on 10.07.2021.
//

#include "slice_view.hpp"

#include <sstream>

using namespace expression_system::utility;

SliceViewInvalidRangeException::SliceViewInvalidRangeException(long min_index, long max_index) noexcept
	: _min_index(min_index), _max_index(max_index) {}


const char* SliceViewInvalidRangeException::what() const noexcept {
	std::stringstream string_stream;
	string_stream << "Min index must be less or equal than max index : " << "Min index = " << _min_index << ", " << "Max index = " << _max_index;
	_message = string_stream.str();
	return _message.c_str();
}


SliceViewOutOfBoundsRangeException::SliceViewOutOfBoundsRangeException(long min_index, long max_index, size_t size) noexcept
	: _min_index(min_index), _max_index(max_index), _size(size) {}


const char* SliceViewOutOfBoundsRangeException::what() const noexcept {
	std::stringstream string_stream;
	string_stream << "Valid range is " << "(" << 0 << ", "<<  _size << "), "  << "Min index = " << _min_index << ", " << "Max index = " << _max_index;
	_message = string_stream.str();
	return _message.c_str();
}
