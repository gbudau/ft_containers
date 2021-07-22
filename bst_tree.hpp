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

  protected:
	allocator_type   m_allocator;
	size_type        m_size;
	// TODO Keep it as root or make it a dummy/header node?
	bst_node_pointer m_root;
	Compare          m_key_compare;
	bst_node_pointer m_allocate_bst_node(const value_type &v) const;
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
	const value_type &value) const {
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

#if 0
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
#endif

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

}  // namespace ft
