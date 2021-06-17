#pragma once
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
class list {
  protected:
	struct list_node;
	typedef typename Allocator::template rebind<list_node>::other node_alloc;

  public:
	// types:
	typedef typename Allocator::reference        reference;
	typedef typename Allocator::const_reference  const_reference;
	typedef typename node_alloc::size_type       size_type;
	typedef typename node_alloc::difference_type difference_type;
	typedef T                                    value_type;
	typedef Allocator                            allocator_type;
	typedef typename Allocator::pointer          pointer;
	typedef typename Allocator::const_pointer    const_pointer;
	/* TODO Define iterator									class
	typedef ft::reverse_iterator<iterator>					reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>
	const_reverse_iterator;
	*/

	// construct/copy/destroy:
	explicit list(const Allocator &allocator = Allocator());

	// capacity:
	size_type size() const;

  protected:
	allocator_type m_allocator;
	size_type      m_length;
	list_node     *m_node;
};

template <class T, class Allocator>
struct list<T, Allocator>::list_node {
	list_node *prev;
	list_node *next;
	T          data;
};

template <class T, class Allocator>
list<T, Allocator>::list(const Allocator &allocator)
	: m_allocator(allocator), m_length(0) {
	node_alloc node_allocator;
	m_node = node_allocator.allocate(1, this);
	m_node->next = m_node;
	m_node->prev = m_node;
}

template <class T, class Allocator>
typename list<T, Allocator>::size_type list<T, Allocator>::size() const {
	return m_length;
}

}  // namespace ft
