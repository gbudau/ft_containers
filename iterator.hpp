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

}  // namespace ft
