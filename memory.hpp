#pragma once
#include <memory>

namespace ft {

// Copies an object to an uninitialized area of memory,
// defined by a range
template <class ForwardIt, class T, class Allocator>
void uninitialized_fill(
	ForwardIt first, ForwardIt last, const T &value, Allocator allocator) {
	while (first != last) {
		allocator.construct(&*first++, value);
	}
}

// Copies an object to an uninitialized area of memory,
// defined by a start
template <class ForwardIt, class Size, class T, class Allocator>
void uninitialized_fill_n(
	ForwardIt first, Size n, const T &value, Allocator allocator) {
	while (n--) {
		allocator.construct(&*first++, value);
	}
}

// Copies a range of objects to an uninitialized area of memory
template <class InputIt, class ForwardIt, class Allocator>
ForwardIt uninitialized_copy(
	InputIt first, InputIt last, ForwardIt d_first, Allocator allocator) {
	while (first != last) {
		allocator.construct(&*d_first++, *first++);
	}
	return d_first;
}

// Destroys a range of objects
template <class ForwardIt, class Allocator>
void destroy(ForwardIt first, ForwardIt last, Allocator allocator) {
	while (first != last) {
		allocator.destroy(first++);
	}
}

}  // namespace ft
