//
// Created by Name on 17.07.2021.
//

#ifndef EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_UTILITY_TRANSFORM_VIEW_HPP_
#define EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_UTILITY_TRANSFORM_VIEW_HPP_

#include <type_traits>
#include <iterator>

namespace expression_system::utility {

template <typename TCollection, typename UnaryOperator>
class TransformView final {
public:

	class Iterator;

private:

	const TCollection& _wrapped_collection;
	UnaryOperator _unary_operator;

public:

	using TCollectionIterator = decltype(std::begin(_wrapped_collection));

	inline TransformView(const TCollection& wrapped_collection, UnaryOperator&& unary_operator);

	inline Iterator begin() const;

	inline Iterator end() const;

	[[nodiscard]] inline size_t size() const;

	inline TCollection& collection();

	inline TCollection& collection() const;
};

template <typename TCollection, typename UnaryOperator>
class TransformView<TCollection, UnaryOperator>::Iterator {
public:

	friend TransformView<TCollection, UnaryOperator>;

private:
	const UnaryOperator& _unary_operator;
public:

	using ValueType
	= typename std::remove_reference<decltype(_unary_operator(*std::begin(TransformView::_wrapped_collection)))>::type;

	inline ValueType operator*() const;

	inline Iterator& operator++();

	inline const TransformView::Iterator operator++(int);

	inline const TransformView::Iterator operator+(int distance) const;

	inline bool operator!=(const Iterator& other) const;

	inline bool operator==(const Iterator& other) const;


private:
	inline explicit Iterator(TCollectionIterator wrapped_iterator, const UnaryOperator& unary_operator) noexcept;

	TCollectionIterator _wrapped_iterator;
};


//////////////////////////////////////////////////////
//                  Implementation                  //
//////////////////////////////////////////////////////


template <typename TCollection, typename UnaryOperator>
TransformView<TCollection, UnaryOperator>::TransformView(const TCollection& wrapped_collection, UnaryOperator&& unary_operator)
	: _wrapped_collection(wrapped_collection), _unary_operator(unary_operator) {
}


template <typename TCollection, typename UnaryOperator>
typename TransformView<TCollection, UnaryOperator>::Iterator TransformView<TCollection, UnaryOperator>::begin() const {
	return TransformView::Iterator(std::begin(_wrapped_collection), _unary_operator);
}


template <typename TCollection, typename UnaryOperator>
typename TransformView<TCollection, UnaryOperator>::Iterator TransformView<TCollection, UnaryOperator>::end() const {
	return TransformView::Iterator(std::end(_wrapped_collection), _unary_operator);
}


template <typename TCollection, typename UnaryOperator>
size_t TransformView<TCollection, UnaryOperator>::size() const {
	return std::distance(begin()._wrapped_iterator, end()._wrapped_iterator);
}


template <typename TCollection, typename UnaryOperator>
TCollection& TransformView<TCollection, UnaryOperator>::collection() {
	return _wrapped_collection;
}


template <typename TCollection, typename UnaryOperator>
TCollection& TransformView<TCollection, UnaryOperator>::collection() const {
	return _wrapped_collection;
}


template <typename TCollection, typename UnaryOperator>
typename TransformView<TCollection, UnaryOperator>::Iterator::ValueType TransformView<TCollection, UnaryOperator>::Iterator::operator*() const {
	return _unary_operator(*_wrapped_iterator);
}


template <typename TCollection, typename UnaryOperator>
typename TransformView<TCollection, UnaryOperator>::Iterator& TransformView<TCollection, UnaryOperator>::Iterator::operator++() {
	++_wrapped_iterator;
	return *this;
}


template <typename TCollection, typename UnaryOperator>
const typename TransformView<TCollection, UnaryOperator>::Iterator TransformView<TCollection, UnaryOperator>::Iterator::operator++(int) {
	auto new_iterator = TransformView<TCollection, UnaryOperator>::Iterator(_wrapped_iterator);
	++new_iterator;
	return new_iterator;
}


template <typename TCollection, typename UnaryOperator>
bool TransformView<TCollection, UnaryOperator>::Iterator::operator!=(const typename TransformView<TCollection, UnaryOperator>::Iterator& other) const {
	return _wrapped_iterator != other._wrapped_iterator;
}


template <typename TCollection, typename UnaryOperator>
bool TransformView<TCollection, UnaryOperator>::Iterator::operator==(const typename TransformView<TCollection, UnaryOperator>::Iterator& other) const {
	return !this->operator!=(other);
}


template <typename TCollection, typename UnaryOperator>
TransformView<TCollection, UnaryOperator>::Iterator::Iterator(TransformView<TCollection, UnaryOperator>::TCollectionIterator wrapped_iterator, const UnaryOperator& unary_operator) noexcept
	: _wrapped_iterator(std::move(wrapped_iterator)), _unary_operator(unary_operator) {}


template <typename TCollection , typename UnaryOperator>
const typename TransformView<TCollection, UnaryOperator>::Iterator TransformView<TCollection, UnaryOperator>::Iterator::operator+(int distance) const {
	return TransformView<TCollection, UnaryOperator>::Iterator(std::next(_wrapped_iterator, distance));
}


template <typename TCollection, typename UnaryOperator>
TransformView<TCollection, UnaryOperator> transform(TCollection& collection, UnaryOperator&& unary_operator) {
	return TransformView(collection, unary_operator);
}


}

#endif //EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_UTILITY_TRANSFORM_VIEW_HPP_
