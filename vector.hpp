#pragma once
#include <memory>
#include <iterator>

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
//	template <class InputIterator>
//		vector(InputIterator first, InputIterator last,
//				const Allocator& = Allocator());
	~vector();
//	vector<T, Allocator>& operator=(const vector<T, Allocator>& x);
//	template <class InputIterator>
//		void assign(InputIterator first, InputIterator last);
//	void assign(size_type n, const T& u);
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
//	void		resize(size_type sz, T c = T());
	size_type	capacity() const;
	bool		empty() const;
//	void		reserve(size_type n);
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
//	void		push_back(const T& x);
//	void		pop_back();
	iterator	insert(iterator position, const T& x);
//	void		insert(iterator position, size_type n, const T& x);
//	template <class InputIterator>
//		void insert(iterator position,
//				InputIterator first, InputIterator last);
	iterator	erase(iterator position);
	iterator	erase(iterator first, iterator last);
//	void		swap(vector<T, Allocator>&);
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
vector<T, Allocator>::~vector() {
	clear();
	m_allocator.deallocate(m_begin, m_end_of_storage - m_begin);
}

template <class T, class Allocator>
void	vector<T, Allocator>::clear() {
	for (pointer tmp = m_begin; tmp != m_end; tmp++) {
		m_allocator.destroy(tmp);
	}
	m_end = m_begin;
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
typename vector<T, Allocator>::size_type	vector<T, Allocator>::capacity() const {
	return m_end_of_storage - begin();
}

template <class T, class Allocator>
bool	vector<T, Allocator>::empty() const {
	return begin() == end();
}

/*
template <class T, class Allocator>
void	vector<T, Allocator>::resize(size_type sz, T val) {
}
*/

template <class T, class Allocator>
typename vector<T, Allocator>::allocator_type	vector<T, Allocator>::get_allocator() const {
	return m_allocator;
}

template <class T, class Allocator>
typename vector<T, Allocator>::iterator	vector<T, Allocator>::insert(iterator position, const T& x) {
	if (size() < capacity()) {
		m_allocator.construct(m_end, *(m_end - 1));
		for (iterator it = end(); it != position; it--) {
			*it = *(it - 1);
		}
		*position = x;
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
	return position;
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

}  // namespace ft
