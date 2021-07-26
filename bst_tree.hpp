#pragma once
#include <limits>
#include <memory>
#include "algorithm.hpp"
#include "functional.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include "utility.hpp"
#include "utils.hpp"

namespace ft {

// KeyOfValue is a unary function object that returns
// the first type of a pair
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
	typedef Key                                               key_type;
	typedef Value                                             value_type;
	typedef Allocator                                         allocator_type;
	typedef typename Allocator::pointer                       pointer;
	typedef typename Allocator::const_pointer                 const_pointer;
	typedef Compare                                           key_compare;

	template <bool isconst = false>
	class bst_tree_iterator {
	  public:
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef Value                           value_type;
		typedef
			typename bst_node_allocator_type::difference_type difference_type;
		typedef typename bst_node_allocator_type::size_type   size_type;
		typedef typename ft::choose<isconst, const Value &, Value &>::type
			reference;
		typedef
			typename ft::choose<isconst, const Value *, Value *>::type pointer;

		bst_tree_iterator(
			bst_node_pointer current = 0, bst_node_pointer root = 0)
			: current(current), root(root) {}

		bst_tree_iterator(const bst_tree_iterator<false> &rhs)
			: current(rhs.base()), root(rhs.getRoot()) {}

		reference operator*() const {
			return current->value;
		}

		pointer operator->() const {
			return &(current->value);
		}

		bst_tree_iterator operator++() {
			if (current->right != NULL) {
				current = current->right;
				while (current->left != NULL) {
					current = current->left;
				}
			} else {
				bst_node_pointer trailing = current->parent;
				while (trailing != NULL && current == trailing->right) {
					current = trailing;
					trailing = trailing->parent;
				}
				current = trailing;
			}
			return *this;
		}

		bst_tree_iterator operator++(int) {
			bst_tree_iterator tmp = *this;
			++*this;
			return tmp;
		}

		bst_tree_iterator operator--() {
			if (current == NULL && root) {
				// Case when current == end()
				// For the reverse iterator where rbegin() == end()
				current = root;
				while (current->right) {
					current = current->right;
				}
			} else if (current->left != NULL) {
				current = current->left;
				while (current->left != NULL) {
					current = current->left;
				}
			} else {
				bst_node_pointer trailing = current->parent;
				while (trailing != NULL && current == trailing->left) {
					current = trailing;
					trailing = trailing->parent;
				}
				current = trailing;
			}
			return *this;
		}

		bst_tree_iterator operator--(int) {
			bst_tree_iterator tmp = *this;
			--*this;
			return tmp;
		}

		friend bool operator==(
			const bst_tree_iterator &x, const bst_tree_iterator &y) {
			return x.current == y.current;
		}

		friend bool operator!=(
			const bst_tree_iterator &x, const bst_tree_iterator &y) {
			return !(x.current == y.current);
		}

		bst_node_pointer base() const {
			return current;
		}

		bst_node_pointer getRoot() const {
			return root;
		}

	  protected:
		bst_node_pointer current;
		bst_node_pointer root;
	};

	typedef bst_tree_iterator<false>             iterator;
	typedef bst_tree_iterator<true>              const_iterator;
	typedef ft::reverse_iterator<iterator>       reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

	// construct/copy/destroy
	explicit bst_tree(const Compare &comp = Compare(),
		const Allocator             &allocator = Allocator());
	template <class InputIterator>
	bst_tree(
		typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer,
			InputIterator>::type first,
		InputIterator last, const Compare &comp = Compare(),
		const Allocator &allocator = Allocator());
	bst_tree(const bst_tree<Key, Value, KeyOfValue, Compare, Allocator> &x);
	~bst_tree();
	bst_tree<Key, Value, KeyOfValue, Compare, Allocator> &operator=(
		const bst_tree<Key, Value, KeyOfValue, Compare, Allocator> &x);
	allocator_type           get_allocator() const;

	// iterators:
	iterator                 begin();
	iterator                 begin() const;
	iterator                 end();
	iterator                 end() const;
	reverse_iterator         rbegin();
	const_reverse_iterator   rbegin() const;
	reverse_iterator         rend();
	const_reverse_iterator   rend() const;

	// capacity:
	bool                     empty() const;
	size_type                size() const;
	size_type                max_size() const;

	// modifiers:
	ft::pair<iterator, bool> insert(const value_type &x);
	iterator                 insert(iterator position, const value_type &x);
	template <class InputIterator>
	void insert(
		typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer,
			InputIterator>::type first,
		InputIterator            last);
	void      erase(iterator position);
	size_type erase(const key_type &x);
	void      erase(iterator first, iterator last);
	void      swap(bst_tree<Key, Value, KeyOfValue, Compare, Allocator> &x);
	void      clear();

	// observers:
	Compare   key_comp() const;

	// operations:
	iterator  find(const key_type &x);
	const_iterator               find(const key_type &x) const;
	size_type                    count(const key_type &x) const;
	iterator                     lower_bound(const key_type &x);
	const_iterator               lower_bound(const key_type &x) const;
	iterator                     upper_bound(const key_type &x);
	const_iterator               upper_bound(const key_type &x) const;
	ft::pair<iterator, iterator> equal_range(const key_type &x);
	ft::pair<const_iterator, const_iterator> equal_range(
		const key_type &x) const;

  protected:
	allocator_type   m_allocator;
	size_type        m_size;
	bst_node_pointer m_root;
	Compare          m_key_compare;
	bst_node_pointer m_allocate_bst_node() const;
	void             m_transplant(bst_node_pointer u, bst_node_pointer v);
	bool m_equal_keys(const value_type &x, const value_type &y) const;
	static bst_node_pointer m_minimum(bst_node_pointer x);
	static bst_node_pointer m_maximum(bst_node_pointer x);
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
typename bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::bst_node_pointer
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::m_minimum(
	bst_node_pointer x) {
	while (x != NULL && x->left) {
		x = x->left;
	}
	return x;
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
typename bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::bst_node_pointer
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::m_maximum(
	bst_node_pointer x) {
	while (x != NULL && x->right) {
		x = x->right;
	}
	return x;
}
template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
bool bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::m_equal_keys(
	const value_type &x, const value_type &y) const {
	return !m_key_compare(KeyOfValue()(x), KeyOfValue()(y)) &&
		   !m_key_compare(KeyOfValue()(y), KeyOfValue()(x));
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
typename bst_tree<Key, Value, KeyOfValue, Compare,
	Allocator>::bst_node_allocator_type
	bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::bst_node_allocator;

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
typename bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::bst_node_pointer
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::m_allocate_bst_node()
	const {
	bst_node_pointer node = bst_node_allocator.allocate(1, this);

	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
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
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::bst_tree(
	const bst_tree<Key, Value, KeyOfValue, Compare, Allocator> &x)
	: m_allocator(x.get_allocator()), m_size(0), m_root(NULL),
	  m_key_compare(x.m_key_compare) {
	insert(x.begin(), x.end());
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::~bst_tree() {
	erase(begin(), end());
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
bst_tree<Key, Value, KeyOfValue, Compare, Allocator> &
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::operator=(
	const bst_tree<Key, Value, KeyOfValue, Compare, Allocator> &x) {
	if (this != &x) {
		erase(begin(), end());
		insert(x.begin(), x.end());
	}
	return *this;
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
typename bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::allocator_type
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::get_allocator() const {
	return m_allocator;
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
typename bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::begin() {
	return iterator(m_minimum(m_root), m_root);
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
typename bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::begin() const {
	return iterator(m_minimum(m_root), m_root);
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
typename bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::end() {
	return iterator(NULL, m_root);
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
typename bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::end() const {
	return iterator(NULL, m_root);
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
typename bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::reverse_iterator
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::rbegin() {
	return reverse_iterator(end());
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
typename bst_tree<Key, Value, KeyOfValue, Compare,
	Allocator>::const_reverse_iterator
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::rbegin() const {
	return reverse_iterator(end());
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
typename bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::reverse_iterator
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::rend() {
	return reverse_iterator(begin());
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
typename bst_tree<Key, Value, KeyOfValue, Compare,
	Allocator>::const_reverse_iterator
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::rend() const {
	return reverse_iterator(begin());
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
ft::pair<
	typename bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator,
	bool>
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::insert(
	const value_type &value) {
	bst_node_pointer traverse = m_root;
	bst_node_pointer trailing = NULL;

	while (traverse != NULL && !m_equal_keys(value, traverse->value)) {
		trailing = traverse;
		bool comp =
			m_key_compare(KeyOfValue()(value), KeyOfValue()(traverse->value));
		traverse = comp ? traverse->left : traverse->right;
	}
	if (traverse != NULL) {
		return ft::make_pair(iterator(traverse, m_root), false);
	}

	bst_node_pointer node = m_allocate_bst_node();
	m_allocator.construct(m_allocator.address(node->value), value);
	node->parent = trailing;
	++m_size;
	if (trailing == NULL) {
		m_root = node;
	} else if (m_key_compare(
				   KeyOfValue()(value), KeyOfValue()(trailing->value))) {
		trailing->left = node;
	} else {
		trailing->right = node;
	}
	return ft::make_pair(iterator(node, m_root), true);
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
typename bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::insert(
	iterator position, const value_type &x) {
	// TODO Optimize
	(void)position;
	return insert(x).first;
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

// Make current->parent point to descendent
// And descendent->parent point to current->parent;
template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
void bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::m_transplant(
	bst_node_pointer current, bst_node_pointer descendent) {
	if (current->parent == NULL) {
		m_root = descendent;
	} else if (current == current->parent->left) {
		current->parent->left = descendent;
	} else {
		current->parent->right = descendent;
	}
	if (descendent != NULL) {
		descendent->parent = current->parent;
	}
}

// From https://www.cs.dartmouth.edu/~thc/cs10/lectures/0428/0428.html
template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
void bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::erase(
	iterator position) {
	bst_node_pointer node = position.base();

	if (node->left == NULL) {
		m_transplant(node, node->right);
	} else if (node->right == NULL) {
		m_transplant(node, node->left);
	} else {
		bst_node_pointer successor = m_minimum(node->right);
		if (successor->parent != node) {
			m_transplant(successor, successor->right);
			successor->right = node->right;
			successor->right->parent = successor;
		}
		m_transplant(node, successor);
		successor->left = node->left;
		successor->left->parent = successor;
	}
	m_allocator.destroy(m_allocator.address(node->value));
	bst_node_allocator.deallocate(node, 1);
	--m_size;
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
typename bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::size_type
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::erase(const key_type &x) {
	iterator it = find(x);

	if (it == end()) {
		return 0;
	}
	erase(it);
	return 1;
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
void bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::erase(
	iterator first, iterator last) {
	while (first != last) {
		erase(first++);
	}
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
void bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::swap(
	bst_tree<Key, Value, KeyOfValue, Compare, Allocator> &x) {
	ft::swap(m_allocator, x.m_allocator);
	ft::swap(m_size, x.m_size);
	ft::swap(m_root, x.m_root);
	ft::swap(m_key_compare, x.m_key_compare);
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
void bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::clear() {
	erase(begin(), end());
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
typename bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::key_compare
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::key_comp() const {
	return m_key_compare;
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
typename bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::find(
	const key_type &key) {
	bst_node_pointer traverse = m_root;

	while (traverse != NULL) {
		const bool comp = m_key_compare(key, KeyOfValue()(traverse->value));
		const bool equalKeys =
			!comp && !m_key_compare(KeyOfValue()(traverse->value), key);
		if (equalKeys) {
			break;
		}
		traverse = comp ? traverse->left : traverse->right;
	}
	return iterator(traverse);
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
typename bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::const_iterator
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::find(
	const key_type &key) const {
	bst_node_pointer traverse = m_root;

	while (traverse != NULL) {
		const bool comp = m_key_compare(key, KeyOfValue()(traverse->value));
		const bool equalKeys =
			!comp && !m_key_compare(KeyOfValue()(traverse->value), key);
		if (equalKeys) {
			break;
		}
		traverse = comp ? traverse->left : traverse->right;
	}
	return iterator(traverse);
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
typename bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::size_type
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::count(
	const key_type &key) const {
	return find(key) == end() ? 0 : 1;
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
typename bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::lower_bound(
	const key_type &key) {
	bst_node_pointer trailing = NULL;
	bst_node_pointer traverse = m_root;

	while (traverse != NULL) {
		if (m_key_compare(KeyOfValue()(traverse->value), key)) {
			trailing = traverse;
			traverse = traverse->left;
		} else {
			traverse = traverse->right;
		}
	}
	return iterator(trailing);
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
typename bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::const_iterator
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::lower_bound(
	const key_type &key) const {
	bst_node_pointer trailing = NULL;
	bst_node_pointer traverse = m_root;

	while (traverse != NULL) {
		if (m_key_compare(KeyOfValue()(traverse->value), key)) {
			trailing = traverse;
			traverse = traverse->left;
		} else {
			traverse = traverse->right;
		}
	}
	return iterator(trailing);
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
typename bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::upper_bound(
	const key_type &key) {
	bst_node_pointer trailing = NULL;
	bst_node_pointer traverse = m_root;

	while (traverse != NULL) {
		if (m_key_compare(key, KeyOfValue()(traverse->value))) {
			trailing = traverse;
			traverse = traverse->left;
		} else {
			traverse = traverse->right;
		}
	}
	return iterator(trailing);
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
typename bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::const_iterator
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::upper_bound(
	const key_type &key) const {
	bst_node_pointer trailing = NULL;
	bst_node_pointer traverse = m_root;

	while (traverse != NULL) {
		if (m_key_compare(key, KeyOfValue()(traverse->value))) {
			trailing = traverse;
			traverse = traverse->left;
		} else {
			traverse = traverse->right;
		}
	}
	return iterator(trailing);
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
ft::pair<
	typename bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator,
	typename bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator>
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::equal_range(
	const key_type &key) {
	return ft::make_pair(lower_bound(key), upper_bound(key));
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
ft::pair<typename bst_tree<Key, Value, KeyOfValue, Compare,
			 Allocator>::const_iterator,
	typename bst_tree<Key, Value, KeyOfValue, Compare,
		Allocator>::const_iterator>
bst_tree<Key, Value, KeyOfValue, Compare, Allocator>::equal_range(
	const key_type &key) const {
	return ft::make_pair(lower_bound(key), upper_bound(key));
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
bool operator==(const bst_tree<Key, Value, KeyOfValue, Compare, Allocator> &x,
	const bst_tree<Key, Value, KeyOfValue, Compare, Allocator>             &y) {
	return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin());
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
bool operator!=(const bst_tree<Key, Value, KeyOfValue, Compare, Allocator> &x,
	const bst_tree<Key, Value, KeyOfValue, Compare, Allocator>             &y) {
	return !(x == y);
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
bool operator<(const bst_tree<Key, Value, KeyOfValue, Compare, Allocator> &x,
	const bst_tree<Key, Value, KeyOfValue, Compare, Allocator>            &y) {
	return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
bool operator>(const bst_tree<Key, Value, KeyOfValue, Compare, Allocator> &x,
	const bst_tree<Key, Value, KeyOfValue, Compare, Allocator>            &y) {
	return !(x < y);
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
bool operator<=(const bst_tree<Key, Value, KeyOfValue, Compare, Allocator> &x,
	const bst_tree<Key, Value, KeyOfValue, Compare, Allocator>             &y) {
	return !(y < x);
}

template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
bool operator>=(const bst_tree<Key, Value, KeyOfValue, Compare, Allocator> &x,
	const bst_tree<Key, Value, KeyOfValue, Compare, Allocator>             &y) {
	return !(x < y);
}

// specialized algorithms:
template <class Key, class Value, class KeyOfValue, class Compare,
	class Allocator>
void swap(bst_tree<Key, Value, KeyOfValue, Compare, Allocator> &x,
	bst_tree<Key, Value, KeyOfValue, Compare, Allocator>       &y) {
	x.swap(y);
}

}  // namespace ft
