#pragma once
#include <iterator>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include "algorithm.hpp"
#include "iterator.hpp"
#include "memory.hpp"
#include "type_traits.hpp"

namespace ft {

template <class T, class Allocator = std::allocator<T> >
class vector {
  public:
	// types
	typedef typename Allocator::reference         reference;
	typedef typename Allocator::const_reference   const_reference;
	typedef typename Allocator::pointer           iterator;
	typedef typename Allocator::const_pointer     const_iterator;
	typedef typename Allocator::size_type         size_type;
	typedef typename Allocator::difference_type   difference_type;
	typedef T                                     value_type;
	typedef Allocator                             allocator_type;
	typedef typename Allocator::pointer           pointer;
	typedef typename Allocator::const_pointer     const_pointer;
	typedef std::reverse_iterator<iterator>       reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	// constructor/copy/destroy
	explicit vector(const Allocator &allocator = Allocator());
	explicit vector(size_type n, const T &value = T(),
		const Allocator &allocator = Allocator());
	template <class InputIterator>
	vector(typename enable_if<!std::numeric_limits<InputIterator>::is_integer,
			   InputIterator>::type first,
		InputIterator last, const Allocator &allocator = Allocator());
	vector(const vector<T, Allocator> &x);
	~vector();
	vector<T, Allocator> &operator=(const vector<T, Allocator> &x);
	void                  assign(size_type n, const T &u);
	template <class InputIterator>
	void assign(
		typename enable_if<!std::numeric_limits<InputIterator>::is_integer,
			InputIterator>::type first,
		InputIterator            last);
	allocator_type         get_allocator() const;

	// iterators
	iterator               begin();
	const_iterator         begin() const;
	iterator               end();
	const_iterator         end() const;
	reverse_iterator       rbegin();
	const_reverse_iterator rbegin() const;
	reverse_iterator       rend();
	const_reverse_iterator rend() const;

	// capacity
	size_type              size() const;
	size_type              max_size() const;
	void                   resize(size_type n, T val = T());
	size_type              capacity() const;
	bool                   empty() const;
	void                   reserve(size_type n);

	// element access
	reference              operator[](size_type n);
	const_reference        operator[](size_type n) const;
	reference              at(size_type n);
	const_reference        at(size_type n) const;
	reference              front();
	const_reference        front() const;
	reference              back();
	const_reference        back() const;

	// modifiers
	void                   push_back(const T &x);
	void                   pop_back();
	iterator               insert(iterator position, const T &x);
	void                   insert(iterator position, size_type n, const T &x);
	template <class InputIterator>
	void     insert(iterator         position,
			typename enable_if<!std::numeric_limits<InputIterator>::is_integer,
            InputIterator>::type first,
			InputIterator            last);
	iterator erase(iterator position);
	iterator erase(iterator first, iterator last);
	void     swap(vector<T, Allocator> &);
	void     clear();

  protected:
	allocator_type m_allocator;
	iterator       m_begin;
	iterator       m_end;
	iterator       m_end_of_storage;
	size_type      m_calculate_new_capacity(size_type n);
};

template <class T, class Allocator>
bool operator==(const vector<T, Allocator> &x, const vector<T, Allocator> &y);

// template <class T, class Allocator>
// bool	operator< (const vector<T, Allocator& x,
//					const vector<T, Allocator& y);
//
// template <class T, class Allocator>
// bool	operator!=(const vector<T, Allocator& x,
//					const vector<T, Allocator& y);
//
// template <class T, class Allocator>
// bool	operator> (const vector<T, Allocator>& x,
//					const vector<T, Allocator>& y);
//
// template <class T, class Allocator>
// bool	operator>=(const vector<T, Allocator>& x,
//					const vector<T, Allocator>& y);
//
// template <class T, class Allocator>
// bool	operator<=(const vector<T, Allocator>& x,
//					const vector<T, Allocator>& y);

// specialized algorithms
template <class T, class Allocator>
void swap(vector<T, Allocator> &x, vector<T, Allocator> &y);

template <class T, class Allocator>
vector<T, Allocator>::vector(const Allocator &allocator)
	: m_allocator(allocator), m_begin(0), m_end(0), m_end_of_storage(0) {}

template <class T, class Allocator>
vector<T, Allocator>::vector(
	size_type n, const T &value, const Allocator &allocator)
	: m_allocator(allocator), m_begin(m_allocator.allocate(n, this)),
	  m_end(m_begin + n), m_end_of_storage(m_end) {
	ft::uninitialized_fill_n(begin(), n, value, get_allocator());
}

template <class T, class Allocator>
template <class InputIterator>
vector<T, Allocator>::vector(
	typename enable_if<!std::numeric_limits<InputIterator>::is_integer,
		InputIterator>::type first,
	InputIterator last, const Allocator &allocator) {
	size_type n = 0;
	for (InputIterator it = first; it != last; it++) {
		n++;
	}
	m_allocator = allocator;
	m_begin = m_allocator.allocate(n, this);
	m_end = m_begin + n;
	m_end_of_storage = m_end;
	ft::uninitialized_copy(first, last, begin(), get_allocator());
}

template <class T, class Allocator>
vector<T, Allocator>::vector(const vector<T, Allocator> &x) {
	m_allocator = x.get_allocator();
	m_begin = m_allocator.allocate(x.end() - x.begin(), this);
	m_end = m_begin + (x.end() - x.begin());
	m_end_of_storage = m_end;
	ft::uninitialized_copy(x.begin(), x.end(), begin(), get_allocator());
}

template <class T, class Allocator>
vector<T, Allocator>::~vector() {
	clear();
	m_allocator.deallocate(m_begin, m_end_of_storage - m_begin);
}

template <class T, class Allocator>
vector<T, Allocator> &vector<T, Allocator>::operator=(
	const vector<T, Allocator> &x) {
	if (this == &x) {
		return *this;
	}
	if (capacity() < x.size()) {
		clear();
		m_allocator.deallocate(m_begin, m_end_of_storage - m_begin);
		m_begin = m_allocator.allocate(x.end() - x.begin(), this);
		m_end = m_begin + (x.end() - x.begin());
		m_end_of_storage = m_end;
		ft::uninitialized_copy(x.begin(), x.end(), begin(), get_allocator());
	} else if (size() >= x.size()) {
		const_iterator src = x.begin();
		iterator       dst = begin();
		while (src != x.end()) {
			*dst++ = *src++;
		}
		while (dst != end()) {
			m_allocator.destroy(dst);
		}
		m_end = m_begin + x.size();
	} else {
		const_iterator src = x.begin();
		iterator       dst = begin();
		while (dst != end()) {
			*dst++ = *src++;
		}
		ft::uninitialized_copy(src, x.end(), dst, get_allocator());
		m_end = m_begin + x.size();
	}
	return *this;
}

template <class T, class Allocator>
void vector<T, Allocator>::assign(size_type n, const T &u) {
	if (capacity() < n) {
		clear();
		m_allocator.deallocate(begin(), capacity());
		m_begin = m_allocator.allocate(n, this);
		m_end = begin() + n;
		m_end_of_storage = m_end;
		ft::uninitialized_fill(begin(), end(), u, get_allocator());
	} else if (size() > n) {
		iterator dst = begin();
		while (dst != begin() + n) {
			*dst++ = u;
		}
		while (dst != end()) {
			m_allocator.destroy(dst++);
		}
		m_end = begin() + n;
	} else {
		iterator dst = begin();
		while (dst != end()) {
			*dst++ = u;
		}
		ft::uninitialized_fill(dst, begin() + n, u, get_allocator());
		m_end = begin() + n;
	}
}

template <class T, class Allocator>
template <class InputIterator>
void vector<T, Allocator>::assign(
	typename enable_if<!std::numeric_limits<InputIterator>::is_integer,
		InputIterator>::type first,
	InputIterator            last) {
	size_type n = 0;
	for (InputIterator it = first; it != last; it++) {
		n++;
	}
	if (capacity() < n) {
		clear();
		m_allocator.deallocate(begin(), capacity());
		m_begin = m_allocator.allocate(n, this);
		m_end = begin() + n;
		m_end_of_storage = m_end;
		ft::uninitialized_copy(first, last, begin(), get_allocator());
	} else if (size() > n) {
		iterator dst = begin();
		while (dst != begin() + n) {
			*dst++ = *first++;
		}
		while (dst != end()) {
			m_allocator.destroy(dst++);
		}
		m_end = begin() + n;
	} else {
		iterator dst = begin();
		while (dst != end()) {
			*dst++ = *first++;
		}
		while (dst != begin() + n) {
			m_allocator.construct(dst++, *first++);
		}
		m_end = begin() + n;
	}
}

template <class T, class Allocator>
typename vector<T, Allocator>::allocator_type
vector<T, Allocator>::get_allocator() const {
	return m_allocator;
}

template <class T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::begin() {
	return m_begin;
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_iterator
vector<T, Allocator>::begin() const {
	return m_begin;
}

template <class T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::end() {
	return m_end;
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_iterator
vector<T, Allocator>::end() const {
	return m_end;
}

template <class T, class Allocator>
typename vector<T, Allocator>::reverse_iterator vector<T, Allocator>::rbegin() {
	return reverse_iterator(end());
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_reverse_iterator
vector<T, Allocator>::rbegin() const {
	return const_reverse_iterator(end());
}

template <class T, class Allocator>
typename vector<T, Allocator>::reverse_iterator vector<T, Allocator>::rend() {
	return reverse_iterator(begin());
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_reverse_iterator
vector<T, Allocator>::rend() const {
	return const_reverse_iterator(begin());
}

template <class T, class Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::size() const {
	return end() - begin();
}

template <class T, class Allocator>
typename vector<T, Allocator>::size_type
vector<T, Allocator>::max_size() const {
	return m_allocator.max_size();
}

template <class T, class Allocator>
void vector<T, Allocator>::resize(size_type n, T val) {
	if (n > capacity()) {
		iterator new_begin = m_allocator.allocate(n, this);
		iterator dst =
			ft::uninitialized_copy(begin(), end(), new_begin, get_allocator());
		clear();
		m_allocator.deallocate(begin(), capacity());
		m_begin = new_begin;
		m_end = new_begin + n;
		m_end_of_storage = m_end;
		ft::uninitialized_fill(dst, end(), val, get_allocator());
	} else if (n < size()) {
		for (iterator it = begin() + n; it != end(); it++) {
			m_allocator.destroy(it);
		}
		m_end = begin() + n;
	} else {
		ft::uninitialized_fill(end(), begin() + n, val, get_allocator());
		m_end = begin() + n;
	}
}

template <class T, class Allocator>
typename vector<T, Allocator>::size_type
vector<T, Allocator>::capacity() const {
	return m_end_of_storage - begin();
}

template <class T, class Allocator>
bool vector<T, Allocator>::empty() const {
	return begin() == end();
}

template <class T, class Allocator>
void vector<T, Allocator>::reserve(size_type n) {
	if (n <= capacity()) {
		return;
	} else if (n > max_size()) {
		throw std::length_error(std::string("vector: reserve: n > max_size"));
	}
	iterator new_begin = m_allocator.allocate(n, this);
	iterator new_end =
		ft::uninitialized_copy(begin(), end(), new_begin, get_allocator());
	clear();
	m_allocator.deallocate(begin(), capacity());
	m_begin = new_begin;
	m_end = new_end;
	m_end_of_storage = m_begin + n;
}

template <class T, class Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::operator[](
	size_type n) {
	return m_begin[n];
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::operator[](
	size_type n) const {
	return m_begin[n];
}

template <class T, class Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::at(size_type n) {
	if (n >= size()) {
		throw std::out_of_range(std::string("vector: index out of range"));
	}
	return m_begin[n];
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::at(
	size_type n) const {
	if (n >= size()) {
		throw std::out_of_range(std::string("vector: index out of range"));
	}
	return m_begin[n];
}

template <class T, class Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::front() {
	return *m_begin;
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_reference
vector<T, Allocator>::front() const {
	return *m_begin;
}

template <class T, class Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::back() {
	return *(m_end - 1);
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_reference
vector<T, Allocator>::back() const {
	return *(m_end - 1);
}

template <class T, class Allocator>
void vector<T, Allocator>::push_back(const T &x) {
	insert(end(), x);
}

template <class T, class Allocator>
void vector<T, Allocator>::pop_back() {
	if (size()) {
		m_end--;
		m_allocator.destroy(m_end);
	}
}

template <class T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(
	iterator position, const T &x) {
	size_type n = position - begin();
	insert(position, 1, x);
	return begin() + n;
}

template <class T, class Allocator>
void vector<T, Allocator>::insert(
	iterator position, size_type count, const T &x) {
	if (count == 0) {
		return;
	}
	if (size() + count <= capacity()) {
		if (static_cast<size_type>(end() - position) > count) {
			ft::uninitialized_copy(
				end() - count, end(), end(), get_allocator());
			ft::copy_backward(position, end() - count, end());
			ft::fill(position, position + count, x);
		} else {
			ft::uninitialized_copy(
				position, end(), position + count, get_allocator());
			ft::uninitialized_fill_n(
				end(), count - (end() - position), x, get_allocator());
			ft::fill(position, end(), x);
		}
		m_end += count;
	} else {
		size_type new_capacity = m_calculate_new_capacity(count);
		iterator  new_begin = m_allocator.allocate(new_capacity, this);
		iterator  dst = ft::uninitialized_copy(
			 begin(), position, new_begin, get_allocator());
		ft::uninitialized_fill_n(dst, count, x, get_allocator());
		dst = ft::uninitialized_copy(
			position, end(), dst + count, get_allocator());
		clear();
		m_allocator.deallocate(m_begin, m_end_of_storage - m_begin);
		m_begin = new_begin;
		m_end = dst;
		m_end_of_storage = m_begin + new_capacity;
	}
}

template <class T, class Allocator>
template <class InputIterator>
void vector<T, Allocator>::insert(iterator position,
	typename enable_if<!std::numeric_limits<InputIterator>::is_integer,
		InputIterator>::type               first,
	InputIterator                          last) {
	if (first == last) {
		return;
	}
	size_type n = distance(first, last);
	if (size() + n <= capacity()) {
		if (static_cast<size_type>(end() - position) > n) {
			ft::uninitialized_copy(end() - n, end(), end(), get_allocator());
			ft::copy_backward(position, position + n, end());
			ft::copy(first, last, position);
		} else {
			ft::uninitialized_copy(
				position, end(), position + n, get_allocator());
			InputIterator it = first;
			ft::advance(it, end() - position);
			ft::copy(first, it, position);
			ft::uninitialized_copy(it, last, end(), get_allocator());
		}
		m_end += n;
	} else {
		size_type new_capacity = m_calculate_new_capacity(n);
		iterator  new_begin = m_allocator.allocate(new_capacity, this);
		iterator  dst = ft::uninitialized_copy(
			 begin(), position, new_begin, get_allocator());
		ft::uninitialized_copy(position, end(), dst + n, get_allocator());
		ft::uninitialized_copy(first, last, dst, get_allocator());
		dst = ft::uninitialized_copy(position, end(), dst + n, get_allocator());
		clear();
		m_allocator.deallocate(m_begin, m_end_of_storage - m_begin);
		m_begin = new_begin;
		m_end = dst;
		m_end_of_storage = m_begin + new_capacity;
	}
	return;
}

template <class T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(
	iterator position) {
	iterator ret = position;
	for (; position + 1 != end(); position++) {
		*position = *(position + 1);
	}
	m_allocator.destroy(m_end);
	--m_end;
	return ret;
}

template <class T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(
	iterator first, iterator last) {
	iterator src = last;
	iterator dst = first;
	for (; src != end(); dst++, src++) {
		*dst = *src;
	}
	for (iterator it = dst; it != end(); it++) {
		m_allocator.destroy(it);
	}
	m_end = dst;
	return first;
}

template <class T, class Allocator>
void vector<T, Allocator>::swap(vector<T, Allocator> &x) {
	ft::swap(m_allocator, x.m_allocator);
	ft::swap(m_begin, x.m_begin);
	ft::swap(m_end, x.m_end);
	ft::swap(m_end_of_storage, x.m_end_of_storage);
}

template <class T, class Allocator>
void vector<T, Allocator>::clear() {
	for (pointer tmp = m_begin; tmp != m_end; tmp++) {
		m_allocator.destroy(tmp);
	}
	m_end = m_begin;
}

template <class T, class Allocator>
typename vector<T, Allocator>::size_type
vector<T, Allocator>::m_calculate_new_capacity(size_type n) {
	if (max_size() - size() < n) {
		throw std::length_error(
			std::string("vector: capacity: size() + n > max_size"));
	}
	const size_type len = size() + ft::max(size(), n);
	return (len < size() || len > max_size()) ? max_size() : len;
}

template <class T, class Allocator>
bool operator==(const vector<T, Allocator> &x, const vector<T, Allocator> &y) {
	if (x.size() != y.size()) {
		return false;
	}
	for (typename vector<T, Allocator>::size_type i = 0; i < x.size(); i++) {
		if (!(x[i] == y[i])) {
			return false;
		}
	}
	return true;
}

template <class T, class Allocator>
void swap(vector<T, Allocator> &x, vector<T, Allocator> &y) {
	x.swap(y);
}

}  // namespace ft
