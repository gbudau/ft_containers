#pragma once
#include <limits>
#include <memory>
#include "functional.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include "utility.hpp"
#include "utils.hpp"

namespace ft {

// KeyOfValue is a unary functio object that returns
// the first type from a pair, in this case the key of the value
template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
class bst_tree {
  protected:
	struct bst_node;
	typedef typename Allocator::template rebind<bst_node>::other
													  bst_node_allocator_type;
	typedef typename bst_node_allocator_type::pointer bst_node_pointer;
	static bst_node_allocator_type                    bst_node_allocator;

  public:
	// types:
	typedef typename Allocator::reference                     reference;
	typedef typename Allocator::const_reference               const_reference;
	typedef typename bst_node_allocator_type::size_type       size_type;
	typedef typename bst_node_allocator_type::difference_type difference_type;
	typedef Value                                             value_type;
	typedef Allocator                                         allocator_type;
	typedef typename Allocator::pointer                       pointer;
	typedef typename Allocator::const_pointer                 const_pointer;

	// construct/copy/destroy
	explicit bst_tree(const Compare &comp = Compare(),
		const Allocator             &allocator = Allocator());
	template <class InputIterator>
	bst_tree(
		typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer,
			InputIterator>::type first,
		InputIterator last, const Compare &comp = Compare(),
		const Allocator &allocator = Allocator());

	// capacity:
	bool      empty() const;
	size_type size() const;
	size_type max_size() const;

	// modifiers:
	// ft::pair<iterator, bool> insert(const value_type &x);
	// TODO Temporary insert function, until iterator is implemented
	void      insert(const value_type &x);
	template <class InputIterator>
	void insert(
		typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer,
			InputIterator>::type first,
		InputIterator            last);

  protected:
	allocator_type   m_allocator;
	size_type        m_size;
	// TODO Keep it as root or make it a dummy/header node?
	bst_node_pointer m_root;
	Compare          m_key_compare;
	bst_node_pointer m_allocate_bst_node(const value_type &v);
};

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
struct bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::bst_node {
	typedef bst_tree<Key, Value, KeyOfValue, Compare, Allocator> self_type;
	self_type::bst_node_pointer                                  parent;
	self_type::bst_node_pointer                                  left;
	self_type::bst_node_pointer                                  right;
	// Pair of key, mapped_type
	Value                                                        value;
};

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
typename bst_tree<Key, Value, KeyOfValue, Compare,
	Allocator>::bst_node_allocator_type
	bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::bst_node_allocator;

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
typename bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::bst_node_pointer
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::m_allocate_bst_node(
	const value_type &value) {
	bst_node_pointer node = bst_node_allocator.allocate(1, this);
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	m_allocator.construct(m_allocator.address(node->value), value);
	return node;
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::bst_tree(
	const Compare &comp, const Allocator &allocator)
	: m_allocator(allocator), m_size(0), m_root(NULL), m_key_compare(comp) {}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
template <class InputIterator>
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::bst_tree(
	typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer,
		InputIterator>::type first,
	InputIterator last, const Compare &comp, const Allocator &allocator)
	: m_allocator(allocator), m_size(0), m_root(NULL), m_key_compare(comp) {
	insert(first, last);
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
bool bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::empty() const {
	return m_size == 0;
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
typename bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::size_type
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::size() const {
	return m_size;
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
typename bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::size_type
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::max_size() const {
	return bst_node_allocator.max_size();
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
void bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::insert(
	const value_type &value) {
	bst_node_pointer x = m_root;
	bst_node_pointer y = NULL;
	while (x != NULL && KeyOfValue()(value) != KeyOfValue()(x->value)) {
		y = x;
		bool comp = m_key_compare(KeyOfValue()(value), KeyOfValue()(x->value));
		x = comp ? x->left : x->right;
	}
	if (x) {
		// TODO return false (not inserted)
		;
	} else if (y == NULL) {
		m_root = m_allocate_bst_node(value);
		++m_size;
	} else {
		bst_node_pointer z = m_allocate_bst_node(value);
		z->parent = y;
		++m_size;
		if (m_key_compare(KeyOfValue()(value), KeyOfValue()(y->value))) {
			y->left = z;
		} else {
			y->right = z;
		}
	}
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
template <class InputIterator>
void bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::insert(
	typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer,
		InputIterator>::type first,
	InputIterator            last) {
	while (first != last) {
		insert(*first++);
	}
}

}  // namespace ft
