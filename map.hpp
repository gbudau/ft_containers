#pragma once
#include <limits>
#include <memory>
#include "functional.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include "utility.hpp"
#include "utils.hpp"

namespace ft {

template <class Key, class T, class Compare = ft::less<Key>,
	class Allocator = std::allocator<ft::pair<const Key, T> > >
class map {
  public:
	// types:
	typedef Key                                 key_type;
	typedef T                                   mapped_type;
	typedef ft::pair<const Key, T>              value_type;
	typedef Compare                             key_compare;
	typedef typename Allocator::reference       reference;
	typedef typename Allocator::const_reference const_reference;
#if 0
	typedef /* TODO */	iterator;
	typedef /* TODO */	const_iterator;
	typedef /* TODO */	size_type;
	typedef /* TODO */	difference_type;
#endif
	typedef typename Allocator::pointer       pointer;
	typedef typename Allocator::const_pointer const_pointer;
#if 0
	// TODO
	typedef ft::reverse_iterator<iterator> reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
#endif
	class value_compare
		: public ft::binary_function<value_type, value_type, bool> {
		friend class map;

	  protected:
		Compare comp;
		value_compare(Compare c) : comp(c) {}

	  public:
		bool operator()(const value_type &x, const value_type &y) const {
			return comp(x.first, y.first);
		}
	};

	// construct/copy/destroy:
	explicit map(const Compare &comp = Compare(),
		const Allocator        &allocator = Allocator());
	template <class InputIterator>
	map(typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer,
			InputIterator>::type first,
		InputIterator last, const Compare &comp = Compare(),
		const Allocator &Allocator = Allocator());
	map(const map<Key, T, Compare, Allocator> &x);
	~map();
	map<Key, T, Compare, Allocator> &operator=(
		const map<Key, T, Compare, Allocator> &x);

#if 0
	// iterators:
	iterator	begin();
	const_iterator	begin() const;
	iterator	end();
	const_iterator	end() const;
	reverse_iterator	rbegin();
	const_reverse_iterator	rbegin() const;
	reverse_iterator	rend();
	const_reverse_iterator	rend() const;
#endif

	// capacity:
	bool      empty() const;
	size_type size() const;
	size_type max_size() const;

	// element access:
	T        &operator[](const key_type &x);

	// modifiers:
#if 0
	ft::pair<iterator, bool> insert(const value_type &x);
	iterator                 insert(iterator position, const value_type &x);
#endif
	template <class InputIterator>
	void insert(InputIterator first, InputIterator last);

#if 0
	void           erase(iterator position);
#endif
	size_type erase(const key_type &x);
#if 0
	void           erase(iterator first, iterator last);
#endif
	void          swap(map<Key, T, Compare, Allocator> &x);
	void          clear();

	// observers:
	key_compare   key_comp() const;
	value_compare value_comp() const;

	// map operations:
#if 0
	iterator       find(const key_type &x);
	const_iterator find(const key_type &x) const;
#endif
	size_type count(const key_type &x) const;

#if 0
	iterator       lower_bound(const key_type &x);
	const_iterator lower_bound(const key_type &x) const;
	iterator       upper_bound(const key_type &x);
	const_iterator upper_bound(const key_type &x) const;

	ft::pair<iterator, iterator>             equal_range(const key_type &x);
	ft::pair<const_iterator, const_iterator> equal_range(
		const key_type &x) const;
#endif
};

template <class Key, class T, class Compare, class Allocator>
bool operator==(const map<Key, T, Compare, Allocator> &x,
	const map<Key, T, Compare, Allocator>             &y);

template <class Key, class T, class Compare, class Allocator>
bool operator!=(const map<Key, T, Compare, Allocator> &x,
	const map<Key, T, Compare, Allocator>             &y);

template <class Key, class T, class Compare, class Allocator>
bool operator<(const map<Key, T, Compare, Allocator> &x,
	const map<Key, T, Compare, Allocator>            &y);

template <class Key, class T, class Compare, class Allocator>
bool operator>(const map<Key, T, Compare, Allocator> &x,
	const map<Key, T, Compare, Allocator>            &y);

template <class Key, class T, class Compare, class Allocator>
bool operator<=(const map<Key, T, Compare, Allocator> &x,
	const map<Key, T, Compare, Allocator>             &y);

template <class Key, class T, class Compare, class Allocator>
bool operator>=(const map<Key, T, Compare, Allocator> &x,
	const map<Key, T, Compare, Allocator>             &y);

// specialized algorithms:
template <class Key, class T, class Compare, class Allocator>
void swap(
	map<Key, T, Compare, Allocator> &x, map<Key, T, Compare, Allocator> &y);

}  // namespace ft
