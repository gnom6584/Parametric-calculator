//
// Created by Name on 10.07.2021.
//

#ifndef BATYA_STONKS_EXPRESSION_SYSTEM_SLICE_VIEW_HPP_
#define BATYA_STONKS_EXPRESSION_SYSTEM_SLICE_VIEW_HPP_

#include <type_traits>
#include <iterator>
#include <string>

namespace expression_system::utility {

template <typename TCollection>
class SliceView final {
public:

	class Iterator;

private:

	TCollection& _wrapped_collection;

public:

	using TCollectionIterator = decltype(std::begin(_wrapped_collection));

	const long min_index;

	const long max_index;

	inline SliceView(TCollection& wrapped_collection, long min_index, long max_index);

	inline Iterator begin() const;

	inline Iterator end() const;

	inline TCollection& collection();

	inline TCollection& collection() const;

	[[nodiscard]] inline size_t size() const;
};

template <typename TCollection>
class SliceView<TCollection>::Iterator {
public:

	friend SliceView<TCollection>;

	using ValueType
	= typename std::remove_reference<decltype(*std::begin(SliceView::_wrapped_collection))>::type;

	using ValuePointerType
	= ValueType*;

	using ValueReferenceType
	= ValueType&;

	inline ValueReferenceType operator*();

	inline ValuePointerType operator->();

	inline ValueReferenceType operator*() const;

	inline ValuePointerType operator->() const;

	inline Iterator& operator++();

	inline Iterator& operator--();

	inline const Iterator operator++(int);

	inline const Iterator operator+(int distance) const;

	inline bool operator==(const Iterator& other) const;

	inline bool operator!=(const Iterator& other) const;

private:
	inline explicit Iterator(TCollectionIterator&& wrapped_iterator) noexcept;

	TCollectionIterator _wrapped_iterator;
};


struct SliceViewException : public std::exception {

};

struct SliceViewInvalidRangeException : public SliceViewException {
public:

	SliceViewInvalidRangeException(long min_index, long max_index) noexcept;

	[[nodiscard]] const char* what() const noexcept override;

private:
	mutable std::string _message;

	const long _min_index;

	const long _max_index;
};

struct SliceViewOutOfBoundsRangeException : public SliceViewException {

	SliceViewOutOfBoundsRangeException(long min_index, long max_index, size_t size) noexcept;

	[[nodiscard]] const char* what() const noexcept override;

private:
	mutable std::string _message;

	const long _min_index;

	const long _max_index;

	const size_t _size;
};


//////////////////////////////////////////////////////
//                  Implementation                  //
//////////////////////////////////////////////////////


template <typename TCollection>
SliceView<TCollection>::SliceView(TCollection& wrapped_collection, long min_index, long max_index)
	: _wrapped_collection(wrapped_collection), min_index(min_index), max_index(max_index) {

	if (min_index > max_index)
		throw SliceViewInvalidRangeException(min_index, max_index);

	const auto size = std::size(wrapped_collection);
	if (min_index < 0 || max_index > size)
		throw SliceViewOutOfBoundsRangeException(min_index, max_index, size);
}


template <typename TCollection>
typename SliceView<TCollection>::Iterator SliceView<TCollection>::begin() const {
	return SliceView::Iterator(std::next(std::begin(_wrapped_collection), min_index));
}


template <typename TCollection>
typename SliceView<TCollection>::Iterator SliceView<TCollection>::end() const {
	return SliceView::Iterator(std::next(std::begin(_wrapped_collection), max_index));
}


template <typename TCollection>
size_t SliceView<TCollection>::size() const {
	return max_index - min_index;
}


template <typename TCollection>
TCollection& SliceView<TCollection>::collection() {
	return _wrapped_collection;
}


template <typename TCollection>
TCollection& SliceView<TCollection>::collection() const {
	return _wrapped_collection;
}


template <typename TCollection>
typename SliceView<TCollection>::Iterator::ValueReferenceType SliceView<TCollection>::Iterator::operator*() {
	return *_wrapped_iterator;
}


template <typename TCollection>
typename SliceView<TCollection>::Iterator::ValuePointerType SliceView<TCollection>::Iterator::operator->() {
	return _wrapped_iterator.operator->();
}


template <typename TCollection>
typename SliceView<TCollection>::Iterator::ValueReferenceType SliceView<TCollection>::Iterator::operator*() const {
	return *_wrapped_iterator;
}


template <typename TCollection>
typename SliceView<TCollection>::Iterator::ValuePointerType SliceView<TCollection>::Iterator::operator->() const {
	return _wrapped_iterator.operator->();
}


template <typename TCollection>
typename SliceView<TCollection>::Iterator& SliceView<TCollection>::Iterator::operator++() {
	++_wrapped_iterator;
	return *this;
}


template <typename TCollection>
typename SliceView<TCollection>::Iterator& SliceView<TCollection>::Iterator::operator--() {
	--_wrapped_iterator;
	return *this;
}


template <typename TCollection>
const typename SliceView<TCollection>::Iterator SliceView<TCollection>::Iterator::operator++(int) {
	auto new_iterator = *this;
	++new_iterator;
	return new_iterator;
}


template <typename TCollection>
bool SliceView<TCollection>::Iterator::operator!=(const typename SliceView<TCollection>::Iterator& other) const {
	return _wrapped_iterator != other._wrapped_iterator;
}


template <typename TCollection>
bool SliceView<TCollection>::Iterator::operator==(const typename SliceView<TCollection>::Iterator& other) const {
	return !this->operator!=(other);
}


template <typename TCollection>
SliceView<TCollection>::Iterator::Iterator(SliceView<TCollection>::TCollectionIterator&& wrapped_iterator) noexcept
	: _wrapped_iterator(wrapped_iterator) {}


template <typename TCollection>
const typename SliceView<TCollection>::Iterator SliceView<TCollection>::Iterator::operator+(int distance) const {
	return SliceView<TCollection>::Iterator(std::next(_wrapped_iterator, distance));
}


template <typename TCollection>
SliceView<TCollection> slice(TCollection& collection, int min, int max) {
	return SliceView<TCollection>(collection, min, max);
}

}
#endif //BATYA_STONKS_EXPRESSION_SYSTEM_SLICE_VIEW_HPP_
