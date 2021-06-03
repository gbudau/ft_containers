#pragma once
#include <iterator>

namespace ft {

template <class InputIterator>
typename std::iterator_traits<InputIterator>::difference_type distance(
	InputIterator first, InputIterator last) {
	typename std::iterator_traits<InputIterator>::difference_type result = 0;
	while (first != last) {
		first++;
		result++;
	}
	return result;
}

template <class InputIterator, class Distance>
void advance(InputIterator& it, Distance n) {
	while (n--) {
		++it;
	}
}

}  // namespace ft
