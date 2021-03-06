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
	reverse_iterator() {}
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

template <class Iterator>
bool operator==(
	const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator> &y) {
	return x.base() == y.base();
}

template <class Iterator>
bool operator!=(
	const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator> &y) {
	return !(x == y);
}

template <class Iterator>
bool operator<(
	const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator> &y) {
	return y.base() < x.base();
}

template <class Iterator>
bool operator>(
	const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator> &y) {
	return y < x;
}

template <class Iterator>
bool operator<=(
	const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator> &y) {
	return !(y < x);
}

template <class Iterator>
bool operator>=(
	const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator> &y) {
	return !(x < y);
}

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator-(
	const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator> &y) {
	return y.base() - x.base();
}

template <class Iterator>
reverse_iterator<Iterator> operator+(
	typename reverse_iterator<Iterator>::difference_type n,
	const reverse_iterator<Iterator>                    &x) {
	return reverse_iterator<Iterator>(x.base() - n);
}

// Fixes for the comparison of reverse_iterator to const reverse_iterator.
template <class IteratorL, class IteratorR>
bool operator==(const reverse_iterator<IteratorL> &x,
	const reverse_iterator<IteratorR>             &y) {
	return x.base() == y.base();
}

template <class IteratorL, class IteratorR>
bool operator!=(const reverse_iterator<IteratorL> &x,
	const reverse_iterator<IteratorR>             &y) {
	return x.base() != y.base();
}

template <class IteratorL, class IteratorR>
bool operator<(const reverse_iterator<IteratorL> &x,
	const reverse_iterator<IteratorR>            &y) {
	return x.base() > y.base();
}

template <class IteratorL, class IteratorR>
bool operator>(const reverse_iterator<IteratorL> &x,
	const reverse_iterator<IteratorR>            &y) {
	return x.base() < y.base();
}

template <class IteratorL, class IteratorR>
bool operator<=(const reverse_iterator<IteratorL> &x,
	const reverse_iterator<IteratorR>             &y) {
	return x.base() >= y.base();
}

template <class IteratorL, class IteratorR>
bool operator>=(const reverse_iterator<IteratorL> &x,
	const reverse_iterator<IteratorR>             &y) {
	return x.base() <= y.base();
}

template <class IteratorL, class IteratorR>
typename reverse_iterator<IteratorL>::difference_type operator-(
	const reverse_iterator<IteratorL> &x,
	const reverse_iterator<IteratorR> &y) {
	return y.base() - x.base();
}

// distance implementation via tag dispatch
namespace detail {

template <class It>
typename ft::iterator_traits<It>::difference_type do_distance(
	It first, It last, std::input_iterator_tag) {
	typename iterator_traits<It>::difference_type result = 0;
	while (first != last) {
		first++;
		result++;
	}
	return result;
}

template <class It>
typename ft::iterator_traits<It>::difference_type do_distance(
	It first, It last, std::random_access_iterator_tag) {
	return last - first;
}

}  // namespace detail

// Returns the distance between two iterators
template <class It>
typename iterator_traits<It>::difference_type distance(It first, It last) {
	return detail::do_distance(
		first, last, typename ft::iterator_traits<It>::iterator_category());
}

// advance implementation via tag dispatch
namespace detail {

template <class It>
void do_advance(It &it, typename ft::iterator_traits<It>::difference_type n,
	std::input_iterator_tag) {
	while (n > 0) {
		--n;
		++it;
	}
}

template <class It>
void do_advance(It &it, typename ft::iterator_traits<It>::difference_type n,
	std::bidirectional_iterator_tag) {
	while (n > 0) {
		--n;
		++it;
	}
	while (n < 0) {
		++n;
		--it;
	}
}

template <class It>
void do_advance(It &it, typename ft::iterator_traits<It>::difference_type n,
	std::random_access_iterator_tag) {
	it += n;
}

}  // namespace detail

// Advances an iterator by given distance
template <class It, class Distance>
void advance(It &it, Distance n) {
	detail::do_advance(it,
		typename std::iterator_traits<It>::difference_type(n),
		typename ft::iterator_traits<It>::iterator_category());
}

// Decrement an iterator
template <class BidirIt>
BidirIt prev(
	BidirIt it, typename ft::iterator_traits<BidirIt>::difference_type n = 1) {
	ft::advance(it, -n);
	return it;
}

// Increment an iterator
template <class InputIt>
InputIt next(
	InputIt it, typename ft::iterator_traits<InputIt>::difference_type n = 1) {
	ft::advance(it, n);
	return it;
}

}  // namespace ft
