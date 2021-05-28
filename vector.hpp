#pragma once
#include <memory>
#include <iterator>
#include <limits>
#include "type_traits.hpp"
#include "algorithm.hpp"

namespace ft {

template <class T, class Allocator = std::allocator<T> >
class vector {
public:
	// types
	typedef typename Allocator::reference			reference;
	typedef typename Allocator::const_reference		const_referenct;
	typedef typename Allocator::pointer				iterator;
	typedef typename Allocator::const_pointer		const_iterator;
	typedef typename Allocator::size_type			size_type;
	typedef typename Allocator::difference_type		difference_type;
	typedef T										value_type;
	typedef Allocator								allocator_type;
	typedef typename Allocator::pointer				pointer;
	typedef	typename Allocator::const_pointer		const_pointer;
	typedef std::reverse_iterator<iterator>			reverse_iterator;
	typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;

	// constructor/copy/destroy
	explicit vector(const Allocator& = Allocator());
	explicit vector(size_type n, const T& value = T(),
			const Allocator& = Allocator());
	template <class InputIterator>
		vector(typename enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type first,
				InputIterator last,
				const Allocator& = Allocator());
	vector(const vector<T,Allocator>& x);
	~vector();
	vector<T, Allocator>& operator=(const vector<T, Allocator>& x);
//	void assign(size_type n, const T& u);
//	template <class InputIterator>
//		void assign(InputIterator first, InputIterator last);
	allocator_type	get_allocator() const;
//
//	// iterators
	iterator				begin();
	const_iterator			begin() const;
	iterator				end();
	const_iterator			end() const;
//	reverse_iterator		rbegin();
//	const_reverse_iterator	rbegin() const;
//	reverse_iterator		rend();
//	const_reverse_iterator	rend() const;
//
//	// capacity
	size_type	size() const;
	size_type	max_size() const;
	void		resize(size_type n, T val = T());
	size_type	capacity() const;
	bool		empty() const;
	void		reserve(size_type n);
//
//
//	// element access
//	reference		operator[](size_type n);
//	const_reference	operator[](size_type n) const;
//	reference		at(size_type n);
//	const_reference	at(size_type n) const;
//	reference		front();
//	const_reference	front() const;
//	reference		back();
//	const_reference	back() const;
//
//	// modifiers
	void		push_back(const T& x);
	void		pop_back();
	iterator	insert(iterator position, const T& x);
//	void		insert(iterator position, size_type n, const T& x);
//	template <class InputIterator>
//		void insert(iterator position,
//				InputIterator first, InputIterator last);
	iterator	erase(iterator position);
	iterator	erase(iterator first, iterator last);
	void		swap(vector<T, Allocator>&);
	void		clear();

protected:
	allocator_type	m_allocator;
	iterator		m_begin;
	iterator		m_end;
	iterator		m_end_of_storage;
};

//template <class T, class Allocator>
//bool	operator==(const vector<T, Allocator>& x,
//	 				const vector<T, Allocator>& y);
//
//template <class T, class Allocator>
//bool	operator< (const vector<T, Allocator& x,
//					const vector<T, Allocator& y);
//
//template <class T, class Allocator>
//bool	operator!=(const vector<T, Allocator& x,
//					const vector<T, Allocator& y);
//
//template <class T, class Allocator>
//bool	operator> (const vector<T, Allocator>& x,
//					const vector<T, Allocator>& y);
//
//template <class T, class Allocator>
//bool	operator>=(const vector<T, Allocator>& x,
//					const vector<T, Allocator>& y);
//
//template <class T, class Allocator>
//bool	operator<=(const vector<T, Allocator>& x,
//					const vector<T, Allocator>& y);
//
//// specialized algorithms
//template <class T, class Allocator>
//void	swap(vector<T, Allocator>& x, vector<T, Allocator>& y);

template <class T, class Allocator>
vector<T, Allocator>::vector(const Allocator& allocator)
	: m_allocator(allocator), m_begin(0), m_end(0), m_end_of_storage(0) {
}

template <class T, class Allocator>
vector<T, Allocator>::vector(size_type n, const T& value,
							const Allocator& allocator)
	: m_allocator(allocator), m_begin(m_allocator.allocate(n, this)),
	m_end(m_begin + n), m_end_of_storage(m_end) {
	for (size_type i = 0; i < n; i++) {
		m_allocator.construct(m_begin + i, value);
	}
}

template <class T, class Allocator>
template <class InputIterator>
vector<T, Allocator>::vector(
		typename enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type first,
		InputIterator last,
		const Allocator& allocator) {
	size_type	n = 0;
	for (InputIterator it = first; it != last; it++) {
		n++;
	}
	m_allocator = allocator;
	m_begin = m_allocator.allocate(n, this);
	m_end = m_begin + n;
	m_end_of_storage = m_end;
	for (iterator dst = begin(); first != last; dst++, first++) {
		m_allocator.construct(dst, *first);
	}
}

template <class T, class Allocator>
vector<T, Allocator>::vector(const vector<T, Allocator>& x) {
	m_allocator = x.get_allocator();
	m_begin = m_allocator.allocate(x.end() - x.begin(), this);
	m_end = m_begin + (x.end() - x.begin());
	m_end_of_storage = m_end;
	const_iterator src = x.begin();
	for (iterator dst = begin(); src != x.end(); dst++, src++) {
		m_allocator.construct(dst, *src);
	}
}

template <class T, class Allocator>
vector<T, Allocator>::~vector() {
	clear();
	m_allocator.deallocate(m_begin, m_end_of_storage - m_begin);
}

template <class T, class Allocator>
vector<T, Allocator>&	vector<T, Allocator>::operator=(const vector<T, Allocator>& x) {
	if (this == &x) {
		return *this;
	}
	if (capacity() < x.size()) {
		clear();
		m_allocator.deallocate(m_begin, m_end_of_storage - m_begin);
		m_begin = m_allocator.allocate(x.end() - x.begin(), this);
		m_end = m_begin + (x.end() - x.begin());
		m_end_of_storage = m_end;
		const_iterator src = x.begin();
		for (iterator dst = begin(); src != x.end(); dst++, src++) {
			m_allocator.construct(dst, *src);
		}
	} else if (size() >= x.size()) {
		const_iterator src = x.begin();
		iterator	dst = begin();
		while (src != x.end()) {
			*dst++ = *src++;
		}
		while (dst != end()) {
			m_allocator.destroy(dst);
		}
		m_end = m_begin + x.size();
	} else {
		const_iterator	src = x.begin();
		iterator	dst = begin();
		while (dst != end()) {
			*dst++ = *src++;
		}
		while (src != x.end()) {
			m_allocator.construct(dst, *src++);
		}
		m_end = m_begin + x.size();;
	}
	return *this;
}

template <class T, class Allocator>
typename vector<T, Allocator>::allocator_type	vector<T, Allocator>::get_allocator() const {
	return m_allocator;
}

template <class T, class Allocator>
typename vector<T, Allocator>::iterator	vector<T, Allocator>::begin() {
	return m_begin;
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_iterator	vector<T, Allocator>::begin() const {
	return m_begin;
}

template <class T, class Allocator>
typename vector<T, Allocator>::iterator	vector<T, Allocator>::end() {
	return m_end;
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_iterator	vector<T, Allocator>::end() const {
	return m_end;
}

template <class T, class Allocator>
typename vector<T, Allocator>::size_type	vector<T, Allocator>::size() const {
	return end() - begin();
}

template <class T, class Allocator>
typename vector<T, Allocator>::size_type	vector<T, Allocator>::max_size() const {
	return m_allocator.max_size();
}

template <class T, class Allocator>
void	vector<T, Allocator>::resize(size_type n, T val) {
	if (n > capacity()) {
		iterator new_begin = m_allocator.allocate(n, this);
		const_iterator	src = begin();
		iterator	dst = new_begin;
		while (src != end()) {
			m_allocator.construct(dst++, *src++);
		}
		clear();
		m_allocator.deallocate(begin(), capacity());
		m_begin = new_begin;
		m_end = new_begin + n;
		m_end_of_storage = m_end;
		while (dst != end()) {
			m_allocator.construct(dst++, val);
		}
	} else if (n < size()) {
		for (iterator it = begin() + n; it != end(); it++) {
			m_allocator.destroy(it);
		}
		m_end = begin() + n;
	} else {
		for (iterator it = end(); it != begin() + n; it++) {
			m_allocator.construct(it, val);
		}
		m_end = begin() + n;
	}
}

template <class T, class Allocator>
typename vector<T, Allocator>::size_type	vector<T, Allocator>::capacity() const {
	return m_end_of_storage - begin();
}

template <class T, class Allocator>
bool	vector<T, Allocator>::empty() const {
	return begin() == end();
}

template <class T, class Allocator>
void	vector<T, Allocator>::reserve(size_type n) {
	if (n <= capacity()) {
		return;
	}
	iterator		new_begin = m_allocator.allocate(n, this);
	const_iterator	src = begin();
	iterator		dst = new_begin;
	while (src != end()) {
		m_allocator.construct(dst++, *src++);
	}
	clear();
	m_allocator.deallocate(begin(), capacity());
	m_begin = new_begin;
	m_end = dst;
	m_end_of_storage = m_begin + n;
}

template <class T, class Allocator>
void	vector<T, Allocator>::push_back(const T& x) {
	insert(end(), x);
}

template <class T, class Allocator>
void	vector<T, Allocator>::pop_back() {
	if (size()) {
		m_end--;
		m_allocator.destroy(m_end);
	}
}

template <class T, class Allocator>
typename vector<T, Allocator>::iterator	vector<T, Allocator>::insert(iterator position, const T& x) {
	size_type	n = end() - position;
	if (size() < capacity()) {
		if (!size()) {
			m_allocator.construct(m_begin, x);
		} else {
			m_allocator.construct(m_end, *(m_end - 1));
			for (iterator it = end(); it != position; it--) {
				*it = *(it - 1);
			}
			*position = x;
		}
		m_end++;
	} else {
		size_type new_capacity = capacity() ? capacity() * 2 : 1;
		iterator new_begin = m_allocator.allocate(new_capacity, this);
		iterator dst = new_begin;
		for (iterator src = begin();  src != position; dst++, src++) {
			m_allocator.construct(dst, *src);
		}
		m_allocator.construct(dst++, x);
		for (iterator src = position; src != end(); dst++, src++) {
			m_allocator.construct(dst, *src);
		}
		clear();
		m_allocator.deallocate(m_begin, m_end_of_storage - m_begin);
		m_begin = new_begin;
		m_end = dst;
		m_end_of_storage = m_begin + new_capacity;
	}
	return begin() + n;
}

template <class T, class Allocator>
typename vector<T, Allocator>::iterator	vector<T, Allocator>::erase(iterator position) {
	iterator ret = position;
	for (;position + 1 != end(); position++) {
		*position = *(position + 1);
	}
	m_allocator.destroy(m_end);
	--m_end;
	return ret;
}

template <class T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(iterator first, iterator last) {
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
void	vector<T, Allocator>::swap(vector<T, Allocator>& x) {
	ft::swap(m_allocator, x.m_allocator);
	ft::swap(m_begin, x.m_begin);
	ft::swap(m_end, x.m_end);
	ft::swap(m_end_of_storage, x.m_end_of_storage);
}

template <class T, class Allocator>
void	vector<T, Allocator>::clear() {
	for (pointer tmp = m_begin; tmp != m_end; tmp++) {
		m_allocator.destroy(tmp);
	}
	m_end = m_begin;
}

}  // namespace ft
