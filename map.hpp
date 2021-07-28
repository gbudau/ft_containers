#pragma once
#include <memory>
#include "bst_tree.hpp"
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
	typedef Allocator                           allocator_type;
	typedef typename Allocator::reference       reference;
	typedef typename Allocator::const_reference const_reference;
	typedef typename Allocator::pointer         pointer;
	typedef typename Allocator::const_pointer   const_pointer;

  private:
	typedef bst_tree<key_type, value_type, select_first<value_type, key_type>,
		key_compare, allocator_type>
			 rep_type;
	rep_type m_tree;

  public:
	// types:
	typedef typename rep_type::iterator               iterator;
	typedef typename rep_type::const_iterator         const_iterator;
	typedef typename rep_type::size_type              size_type;
	typedef typename rep_type::difference_type        difference_type;
	typedef typename rep_type::reverse_iterator       reverse_iterator;
	typedef typename rep_type::const_reverse_iterator const_reverse_iterator;

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
		const Allocator        &allocator = Allocator())
		: m_tree(comp, allocator) {}
	template <class InputIterator>
	map(typename ft::enable_if<!ft::is_integral<InputIterator>::value,
			InputIterator>::type first,
		InputIterator last, const Compare &comp = Compare(),
		const Allocator &allocator = Allocator())
		: m_tree(first, last, comp, allocator) {}
	map(const map<Key, T, Compare, Allocator> &x) : m_tree(x.m_tree) {}
	~map() {}
	map<Key, T, Compare, Allocator> &operator=(
		const map<Key, T, Compare, Allocator> &x) {
		m_tree = x.m_tree;
		return *this;
	}

	allocator_type get_allocator() const {
		return m_tree.get_allocator();
	}

	// iterators:
	iterator begin() {
		return m_tree.begin();
	}

	const_iterator begin() const {
		return m_tree.begin();
	}

	iterator end() {
		return m_tree.end();
	}

	const_iterator end() const {
		return m_tree.end();
	}

	reverse_iterator rbegin() {
		return m_tree.rbegin();
	}

	const_reverse_iterator rbegin() const {
		return m_tree.rbegin();
	}

	reverse_iterator rend() {
		return m_tree.rend();
	}

	const_reverse_iterator rend() const {
		return m_tree.rend();
	}

	// capacity:
	bool empty() const {
		return m_tree.empty();
	}

	size_type size() const {
		return m_tree.size();
	}

	size_type max_size() const {
		return m_tree.max_size();
	}

	// element access:
	T &operator[](const key_type &key) {
		return insert(ft::make_pair(key, T())).first->second;
	}

	// modifiers:
	ft::pair<iterator, bool> insert(const value_type &x) {
		return m_tree.insert(x);
	}

	iterator insert(iterator position, const value_type &x) {
		return m_tree.insert(position, x);
	}

	template <class InputIterator>
	void insert(InputIterator first, InputIterator last) {
		m_tree.insert(first, last);
	}

	void erase(iterator position) {
		m_tree.erase(position);
	}

	size_type erase(const key_type &key) {
		return m_tree.erase(key);
	}

	void erase(iterator first, iterator last) {
		m_tree.erase(first, last);
	}

	void swap(map<Key, T, Compare, Allocator> &x) {
		m_tree.swap(x.m_tree);
	}

	void clear() {
		m_tree.clear();
	}

	// observers:
	key_compare key_comp() const {
		return m_tree.key_comp();
	}
	value_compare value_comp() const {
		return value_compare(m_tree.key_comp());
	}

	// map operations:
	iterator find(const key_type &key) {
		return m_tree.find(key);
	}

	const_iterator find(const key_type &key) const {
		return m_tree.find(key);
	}

	size_type count(const key_type &key) const {
		return m_tree.count(key);
	}

	iterator lower_bound(const key_type &key) {
		return m_tree.lower_bound(key);
	}

	const_iterator lower_bound(const key_type &key) const {
		return m_tree.lower_bound(key);
	}

	iterator upper_bound(const key_type &key) {
		return m_tree.upper_bound(key);
	}

	const_iterator upper_bound(const key_type &key) const {
		return m_tree.upper_bound(key);
	}

	ft::pair<iterator, iterator> equal_range(const key_type &key) {
		return m_tree.equal_range(key);
	}

	ft::pair<const_iterator, const_iterator> equal_range(
		const key_type &key) const {
		return m_tree.equal_range(key);
	}
};

template <class Key, class T, class Compare, class Allocator>
bool operator==(const map<Key, T, Compare, Allocator> &x,
	const map<Key, T, Compare, Allocator>             &y) {
	return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin());
}

template <class Key, class T, class Compare, class Allocator>
bool operator!=(const map<Key, T, Compare, Allocator> &x,
	const map<Key, T, Compare, Allocator>             &y) {
	return !(x == y);
}

template <class Key, class T, class Compare, class Allocator>
bool operator<(const map<Key, T, Compare, Allocator> &x,
	const map<Key, T, Compare, Allocator>            &y) {
	return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template <class Key, class T, class Compare, class Allocator>
bool operator>(const map<Key, T, Compare, Allocator> &x,
	const map<Key, T, Compare, Allocator>            &y) {
	return y < x;
}

template <class Key, class T, class Compare, class Allocator>
bool operator<=(const map<Key, T, Compare, Allocator> &x,
	const map<Key, T, Compare, Allocator>             &y) {
	return !(y < x);
}

template <class Key, class T, class Compare, class Allocator>
bool operator>=(const map<Key, T, Compare, Allocator> &x,
	const map<Key, T, Compare, Allocator>             &y) {
	return !(x < y);
}

// specialized algorithms:
template <class Key, class T, class Compare, class Allocator>
void swap(
	map<Key, T, Compare, Allocator> &x, map<Key, T, Compare, Allocator> &y) {
	x.swap(y);
}

}  // namespace ft
