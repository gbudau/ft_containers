#pragma once
#include <memory>

namespace ft {

// Copies an object to an uninitialized area of memory,
// defined by a range
template <class ForwardIt, class T, class Allocator>
void uninitialized_fill(ForwardIt first, ForwardIt last, const T &value,
                        Allocator allocator = Allocator()) {
	while (first != last) {
		allocator.construct(&*first++, value);
	}
}

// Copies an object to an uninitialized area of memory,
// defined by a start
template <class ForwardIt, class Size, class T, class Allocator>
void uninitialized_fill_n(ForwardIt first, Size n, const T &value,
                          Allocator allocator = Allocator()) {
	while (n--) {
		allocator.construct(&*first++, value);
	}
}

}  // namespace ft
