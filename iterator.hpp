#pragma once
#include <cstddef>
#include <iterator>

namespace ft {

template <class Iterator>
struct iterator_traits {
	typedef typename Iterator::difference_type   difference_type;
	typedef typename Iterator::value_type        value_type;
	typedef typename Iterator::pointer           pointer;
	typedef typename Iterator::reference         reference;
	typedef typename Iterator::iterator_category iterator_category;
};

template <class T>
struct iterator_traits<T *> {
	typedef std::ptrdiff_t                  difference_type;
	typedef T                               value_type;
	typedef T                              *pointer;
	typedef T                              &reference;
	typedef std::random_access_iterator_tag iterator_category;
};

template <class T>
struct iterator_traits<const T *> {
	typedef std::ptrdiff_t                  difference_type;
	typedef T                               value_type;
	typedef const T                        *pointer;
	typedef const T                        &reference;
	typedef std::random_access_iterator_tag iterator_category;
};

template <class Category, class T, class Distance = std::ptrdiff_t,
	class Pointer = T *, class Reference = T &>
struct iterator {
	typedef T         value_type;
	typedef Distance  difference_type;
	typedef Pointer   pointer;
	typedef Reference reference;
	typedef Category  iterator_category;
};

template <class Iterator>
class reverse_iterator
	: public iterator<typename iterator_traits<Iterator>::iterator_category,
		  typename iterator_traits<Iterator>::value_type,
		  typename iterator_traits<Iterator>::difference_type,
		  typename iterator_traits<Iterator>::pointer,
		  typename iterator_traits<Iterator>::reference> {
  protected:
	Iterator m_current;

  public:
	typedef Iterator                                            iterator_type;
	typedef typename iterator_traits<Iterator>::difference_type difference_type;
	typedef typename iterator_traits<Iterator>::reference       reference;
	typedef typename iterator_traits<Iterator>::pointer         pointer;
	reverse_iterator();
	explicit reverse_iterator(Iterator x);
	template <class U>
	reverse_iterator(const reverse_iterator<U> &u);
	Iterator          base() const;
	reference         operator*() const;
	pointer           operator->() const;

	reverse_iterator &operator++();
	reverse_iterator  operator++(int);
	reverse_iterator &operator--();
	reverse_iterator  operator--(int);

	reverse_iterator  operator+(difference_type n) const;
	reverse_iterator &operator+=(difference_type n);
	reverse_iterator  operator-(difference_type n) const;
	reverse_iterator &operator-=(difference_type n);
	reference         operator[](difference_type n) const;

  private:
	typedef reverse_iterator<Iterator> self;
	friend bool operator==(const self &x, const self &y) {
		return x.m_current == y.m_current;
	}

	friend bool operator!=(const self &x, const self &y) {
		return x.m_current != y.m_current;
	}

	friend bool operator<(const self &x, const self &y) {
		return x.m_current > y.m_current;
	}

	friend bool operator>(const self &x, const self &y) {
		return x.m_current < y.m_current;
	}

	friend bool operator<=(const self &x, const self &y) {
		return x.m_current >= y.m_current;
	}

	friend bool operator>=(const self &x, const self &y) {
		return x.m_current <= y.m_current;
	}

	friend self::difference_type operator-(const self &x, const self &y) {
		return y.m_current - x.m_current;
	}

	friend self operator+(typename self::difference_type n, const self &x) {
		return self(x.m_current - n);
	}
};

template <class Iterator>
reverse_iterator<Iterator>::reverse_iterator(Iterator x) : m_current(x) {}

template <class Iterator>
template <class U>
reverse_iterator<Iterator>::reverse_iterator(const reverse_iterator<U> &u)
	: m_current(u.base()) {}

template <class Iterator>
Iterator reverse_iterator<Iterator>::base() const {
	return m_current;
}

template <class Iterator>
typename reverse_iterator<Iterator>::reference
reverse_iterator<Iterator>::operator*() const {
	Iterator tmp = m_current;
	return *--tmp;
}

template <class Iterator>
typename reverse_iterator<Iterator>::pointer
reverse_iterator<Iterator>::operator->() const {
	return &(operator*());
}

template <class Iterator>
reverse_iterator<Iterator> &reverse_iterator<Iterator>::operator++() {
	--m_current;
	return *this;
}

template <class Iterator>
reverse_iterator<Iterator> reverse_iterator<Iterator>::operator++(int) {
	reverse_iterator tmp = *this;
	--m_current;
	return tmp;
}

template <class Iterator>
reverse_iterator<Iterator> &reverse_iterator<Iterator>::operator--() {
	++m_current;
	return *this;
}

template <class Iterator>
reverse_iterator<Iterator> reverse_iterator<Iterator>::operator--(int) {
	reverse_iterator tmp = *this;
	++m_current;
	return tmp;
}

template <class Iterator>
reverse_iterator<Iterator> reverse_iterator<Iterator>::operator+(
	typename reverse_iterator<Iterator>::difference_type n) const {
	return reverse_iterator(m_current - n);
}

template <class Iterator>
reverse_iterator<Iterator> &reverse_iterator<Iterator>::operator+=(
	typename reverse_iterator<Iterator>::difference_type n) {
	m_current -= n;
	return *this;
}

template <class Iterator>
reverse_iterator<Iterator> reverse_iterator<Iterator>::operator-(
	typename reverse_iterator<Iterator>::difference_type n) const {
	return reverse_iterator(m_current + n);
}

template <class Iterator>
reverse_iterator<Iterator> &reverse_iterator<Iterator>::operator-=(
	typename reverse_iterator<Iterator>::difference_type n) {
	m_current += n;
	return *this;
}

template <class Iterator>
typename reverse_iterator<Iterator>::reference
reverse_iterator<Iterator>::operator[](
	typename reverse_iterator<Iterator>::difference_type n) const {
	return m_current[-n - 1];
}

template <class InputIterator>
typename iterator_traits<InputIterator>::difference_type distance(
	InputIterator first, InputIterator last) {
	typename iterator_traits<InputIterator>::difference_type result = 0;
	while (first != last) {
		first++;
		result++;
	}
	return result;
}

template <class InputIterator, class Distance>
void advance(InputIterator &it, Distance n) {
	while (n--) {
		++it;
	}
}

}  // namespace ft
