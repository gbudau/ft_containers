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
class bst {
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
	typedef T                                                 value_type;
	typedef Allocator                                         allocator_type;
	typedef typename Allocator::pointer                       pointer;
	typedef typename Allocator::const_pointer                 const_pointer;

  protected:
	allocator_type   m_allocator;
	size_type        m_size;
	// TODO Keep it as root or make it a dummy/header node?
	bst_node_pointer m_root;
	Compare          m_key_compare;
};

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
	struct bst < Key,
	Value, KeyOfValue, Compare, Allocator::bst_node {
	typedef bst < Key, Value, KeyOfValue, Compare, Allocator self_type;
	self_type::bst_node_pointer parent;
	self_type::bst_node_pointer left;
	self_type::bst_node_pointer right;
	// Pair of key, mapped_type
	Value                       value;
};

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
	typename bst < Key,
	Value, KeyOfValue, Compare, Allocator::node_allocator_type bst < Key, Value,
	KeyOfValue, Compare, Allocator::node_allocator;

}  // namespace ft
