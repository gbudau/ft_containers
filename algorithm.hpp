#pragma once

namespace ft {

// Swaps the values of two objects
template <typename T>
void swap(T &a, T &b) {
	T tmp = a;
	a = b;
	b = tmp;
}

// returns the lowest of the given values
template <class T>
const T &min(const T &a, const T &b) {
	if (b < a)
		return b;
	return a;
}

// returns the highest of the given values
template <class T>
const T &max(const T &a, const T &b) {
	if (a < b)
		return b;
	return a;
}

// Copy-assigns the given value to every element in a range
template <class ForwardIterator, class T>
void fill(ForwardIterator first, ForwardIterator last, const T &value) {
	while (first != last) {
		*first++ = value;
	}
}

// Copy-assigns the given value to N elements in a range
template <class OutputIterator, class Size, class T>
OutputIterator fill_n(OutputIterator first, Size count, const T &value) {
	for (Size i = 0; i < count; i++) {
		*first++ = value;
	}
	return first;
}

// Copy-assigns the given value to N elements in a range
template <class InputIterator, class OutputIterator>
OutputIterator copy(
	InputIterator first, InputIterator last, OutputIterator d_first) {
	while (first != last) {
		*d_first++ = *first++;
	}
	return d_first;
}

// Copies a range of elements in backwards order
template <class BidirIt1, class BidirIt2>
BidirIt2 copy_backward(BidirIt1 first, BidirIt1 last, BidirIt2 d_last) {
	while (first != last) {
		*--d_last = *--last;
	}
	return d_last;
}

}  // namespace ft
