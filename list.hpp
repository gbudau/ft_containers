#pragma once
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include "algorithm.hpp"
#include "iterator.hpp"
#include "memory.hpp"
#include "type_traits.hpp"
#include "utils.hpp"

namespace ft {

template <class T, class Allocator = std::allocator<T> >
class list {
  protected:
	struct list_node;
	typedef typename Allocator::template rebind<list_node>::other
												  node_allocator_type;
	typedef typename node_allocator_type::pointer node_pointer;
	static node_allocator_type                    node_allocator;

  public:
	// types:
	typedef typename Allocator::reference                 reference;
	typedef typename Allocator::const_reference           const_reference;
	typedef typename node_allocator_type::size_type       size_type;
	typedef typename node_allocator_type::difference_type difference_type;
	typedef T                                             value_type;
	typedef Allocator                                     allocator_type;
	typedef typename Allocator::pointer                   pointer;
	typedef typename Allocator::const_pointer             const_pointer;

	template <bool isconst = false>
	class list_iterator {
	  public:
		typedef std::bidirectional_iterator_tag               iterator_category;
		typedef T                                             value_type;
		typedef typename node_allocator_type::difference_type difference_type;
		typedef typename node_allocator_type::size_type       size_type;
		typedef typename ft::choose<isconst, const T &, T &>::type reference;
		typedef typename ft::choose<isconst, const T *, T *>::type pointer;

		list_iterator(node_pointer x = 0) : current(x) {}

		list_iterator(const list_iterator<false> &rhs) : current(rhs.base()) {}

		reference operator*() const {
			return current->data;
		}
		pointer operator->() const {
			return &(current->data);
		}
		list_iterator &operator++() {
			current = current->next;
			return *this;
		}

		list_iterator operator++(int) {
			list_iterator tmp(*this);
			current = current->next;
			return tmp;
		}

		list_iterator &operator--() {
			current = current->prev;
			return *this;
		}

		list_iterator operator--(int) {
			list_iterator tmp(*this);
			current = current->prev;
			return tmp;
		}

		friend bool operator==(const list_iterator &x, const list_iterator &y) {
			return x.current == y.current;
		}

		friend bool operator!=(const list_iterator &x, const list_iterator &y) {
			return !(x.current == y.current);
		}

		node_pointer base() const {
			return current;
		}

	  protected:
		node_pointer current;
	};

	typedef list_iterator<false>                 iterator;
	typedef list_iterator<true>                  const_iterator;
	typedef ft::reverse_iterator<iterator>       reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

	// construct/copy/destroy:
	explicit list(const Allocator &allocator = Allocator());
	explicit list(size_type n, const T &value = T(),
		const Allocator &allocator = Allocator());
	template <class InputIterator>
	list(typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer,
			 InputIterator>::type first,
		InputIterator last, const Allocator &allocator = Allocator());
	list(const list<T, Allocator> &x);
	~list();
	list<T, Allocator> &operator=(const list<T, Allocator> &x);
	void                assign(size_type n, const T &t);
	template <class InputIterator>
	void assign(
		typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer,
			InputIterator>::type first,
		InputIterator            last);
	allocator_type         get_allocator() const;

	// iterators:
	iterator               begin();
	const_iterator         begin() const;
	iterator               end();
	const_iterator         end() const;
	reverse_iterator       rbegin();
	const_reverse_iterator rbegin() const;
	reverse_iterator       rend();
	const_reverse_iterator rend() const;

	// capacity:
	bool                   empty() const;
	size_type              size() const;
	size_type              max_size() const;
	void                   resize(size_type n, T value = T());

	// element access:
	reference              front();
	const_reference        front() const;
	reference              back();
	const_reference        back() const;

	// modifiers:
	void                   push_front(const T &value);
	void                   pop_front();
	void                   push_back(const T &value);
	void                   pop_back();
	iterator               insert(iterator position, const T &value);
	void insert(iterator position, size_type n, const T &value);
	template <class InputIterator>
	void     insert(iterator         position,
			typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer,
            InputIterator>::type first,
			InputIterator            last);
	iterator erase(iterator position);
	iterator erase(iterator position, iterator last);
	void     swap(list<T, Allocator> &other);
	void     clear();

	// list operations:
	void     splice(iterator position, list<T, Allocator> &other);
	void     splice(iterator position, list<T, Allocator> &other, iterator it);
	void splice(iterator position, list<T, Allocator> &other, iterator first,
		iterator last);

  protected:
	allocator_type m_allocator;
	size_type      m_length;
	node_pointer   m_node;
	node_pointer   m_allocate_node() const;
	void           m_init_header_node();
	void           m_transfer(iterator position, iterator first, iterator last);
};

template <class T, class Allocator>
struct list<T, Allocator>::list_node {
	list<T, Allocator>::node_pointer next;
	list<T, Allocator>::node_pointer prev;
	T                                data;
};

template <class T, class Allocator>
typename list<T, Allocator>::node_allocator_type
	list<T, Allocator>::node_allocator;

template <class T, class Allocator>
typename list<T, Allocator>::node_pointer
list<T, Allocator>::m_allocate_node() const {
	node_pointer node = node_allocator.allocate(1, this);
	return node;
}

template <class T, class Allocator>
void list<T, Allocator>::m_init_header_node() {
	m_node = m_allocate_node();
	m_node->next = m_node;
	m_node->prev = m_node;
}

template <class T, class Allocator>
list<T, Allocator>::list(const Allocator &allocator)
	: m_allocator(allocator), m_length(0) {
	m_init_header_node();
}

template <class T, class Allocator>
list<T, Allocator>::list(
	size_type n, const T &value, const Allocator &allocator)
	: m_allocator(allocator), m_length(0) {
	m_init_header_node();
	insert(end(), n, value);
}

template <class T, class Allocator>
template <class InputIterator>
list<T, Allocator>::list(
	typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer,
		InputIterator>::type first,
	InputIterator last, const Allocator &allocator)
	: m_allocator(allocator), m_length(0) {
	m_init_header_node();
	insert(end(), first, last);
}

template <class T, class Allocator>
list<T, Allocator>::list(const list<T, Allocator> &x)
	: m_allocator(x.get_allocator()), m_length(0) {
	m_init_header_node();
	insert(end(), x.begin(), x.end());
}

template <class T, class Allocator>
list<T, Allocator>::~list() {
	clear();
	node_allocator.deallocate(m_node, 1);
}

template <class T, class Allocator>
list<T, Allocator> &list<T, Allocator>::operator=(const list<T, Allocator> &x) {
	if (this != &x) {
		assign(x.begin(), x.end());
	}
	return *this;
}

template <class T, class Allocator>
void list<T, Allocator>::assign(size_type n, const T &value) {
	clear();
	insert(end(), n, value);
}

template <class T, class Allocator>
template <class InputIterator>
void list<T, Allocator>::assign(
	typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer,
		InputIterator>::type first,
	InputIterator            last) {
	clear();
	insert(end(), first, last);
}

template <class T, class Allocator>
typename list<T, Allocator>::allocator_type
list<T, Allocator>::get_allocator() const {
	return m_allocator;
}

template <class T, class Allocator>
typename list<T, Allocator>::iterator list<T, Allocator>::begin() {
	return m_node->next;
}

template <class T, class Allocator>
typename list<T, Allocator>::const_iterator list<T, Allocator>::begin() const {
	return m_node->next;
}

template <class T, class Allocator>
typename list<T, Allocator>::iterator list<T, Allocator>::end() {
	return m_node;
}

template <class T, class Allocator>
typename list<T, Allocator>::const_iterator list<T, Allocator>::end() const {
	return m_node;
}

template <class T, class Allocator>
typename list<T, Allocator>::reverse_iterator list<T, Allocator>::rbegin() {
	return reverse_iterator(end());
}

template <class T, class Allocator>
typename list<T, Allocator>::const_reverse_iterator
list<T, Allocator>::rbegin() const {
	return reverse_iterator(end());
}

template <class T, class Allocator>
typename list<T, Allocator>::reverse_iterator list<T, Allocator>::rend() {
	return reverse_iterator(begin());
}

template <class T, class Allocator>
typename list<T, Allocator>::const_reverse_iterator
list<T, Allocator>::rend() const {
	return reverse_iterator(begin());
}

template <class T, class Allocator>
bool list<T, Allocator>::empty() const {
	return m_length == 0;
}

template <class T, class Allocator>
typename list<T, Allocator>::size_type list<T, Allocator>::size() const {
	return m_length;
}

template <class T, class Allocator>
typename list<T, Allocator>::size_type list<T, Allocator>::max_size() const {
	return node_allocator.max_size();
}

template <class T, class Allocator>
void list<T, Allocator>::resize(size_type n, T value) {
	if (n > size()) {
		insert(end(), n - size(), value);
	} else if (n < size()) {
		iterator it = begin();
		ft::advance(it, n);
		erase(it, end());
	}
}

template <class T, class Allocator>
typename list<T, Allocator>::reference list<T, Allocator>::front() {
	return *begin();
}

template <class T, class Allocator>
typename list<T, Allocator>::const_reference list<T, Allocator>::front() const {
	return *begin();
}

template <class T, class Allocator>
typename list<T, Allocator>::reference list<T, Allocator>::back() {
	return *ft::prev(end());
}

template <class T, class Allocator>
typename list<T, Allocator>::const_reference list<T, Allocator>::back() const {
	return *ft::prev(end());
}

template <class T, class Allocator>
void list<T, Allocator>::push_front(const T &value) {
	insert(begin(), value);
}

template <class T, class Allocator>
void list<T, Allocator>::pop_front() {
	erase(begin());
}

template <class T, class Allocator>
void list<T, Allocator>::push_back(const T &value) {
	insert(end(), value);
}

template <class T, class Allocator>
void list<T, Allocator>::pop_back() {
	erase(ft::prev(end()));
}

template <class T, class Allocator>
typename list<T, Allocator>::iterator list<T, Allocator>::insert(
	iterator position, const T &value) {
	node_pointer tmp = m_allocate_node();
	m_allocator.construct(m_allocator.address(tmp->data), value);
	tmp->next = position.base();
	tmp->prev = position.base()->prev;
	position.base()->prev->next = tmp;
	position.base()->prev = tmp;
	m_length++;
	return tmp;
}

template <class T, class Allocator>
void list<T, Allocator>::insert(
	iterator position, size_type n, const T &value) {
	while (n--) {
		insert(position, value);
	}
}

template <class T, class Allocator>
template <class InputIterator>
void list<T, Allocator>::insert(iterator position,
	typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer,
		InputIterator>::type             first,
	InputIterator                        last) {
	while (first != last) {
		position = insert(position, *first);
		position++;
		first++;
	}
}

template <class T, class Allocator>
typename list<T, Allocator>::iterator list<T, Allocator>::erase(
	iterator position) {
	iterator next = position.base()->next;
	position.base()->prev->next = position.base()->next;
	position.base()->next->prev = position.base()->prev;
	m_allocator.destroy(m_allocator.address(position.base()->data));
	node_allocator.deallocate(position.base(), 1);
	m_length--;
	return next;
}

template <class T, class Allocator>
typename list<T, Allocator>::iterator list<T, Allocator>::erase(
	iterator position, iterator last) {
	iterator ret = position;
	while (position != last) {
		ret = erase(position++);
	}
	return ret;
}

template <class T, class Allocator>
void list<T, Allocator>::swap(list<T, Allocator> &other) {
	ft::swap(m_allocator, other.m_allocator);
	ft::swap(m_length, other.m_length);
	ft::swap(m_node, other.m_node);
}

template <class T, class Allocator>
void list<T, Allocator>::clear() {
	erase(begin(), end());
}

template <class T, class Allocator>
void list<T, Allocator>::m_transfer(
	iterator position, iterator first, iterator last) {
	last.base()->prev->next = position.base();
	first.base()->prev->next = last.base();
	position.base()->prev->next = first.base();
	node_pointer tmp = position.base()->prev;
	position.base()->prev = last.base()->prev;
	last.base()->prev = first.base()->prev;
	first.base()->prev = tmp;
}

template <class T, class Allocator>
void list<T, Allocator>::splice(iterator position, list<T, Allocator> &other) {
	if (other.empty()) {
		return;
	}
	m_transfer(position, other.begin(), other.end());
	m_length += other.m_length;
	other.m_length = 0;
}

template <class T, class Allocator>
void list<T, Allocator>::splice(
	iterator position, list<T, Allocator> &other, iterator it) {
	iterator it_next = ft::next(it);
	if (position == it || position == it_next) {
		return;
	}
	m_transfer(position, it, it_next);
	++m_length;
	--other.m_length;
}

template <class T, class Allocator>
void list<T, Allocator>::splice(iterator position, list<T, Allocator> &other,
	iterator first, iterator last) {
	if (first == last || last == end()) {
		return;
	}
	if (this != &other) {
		difference_type n = ft::distance(first, last);
		m_length += n;
		other.m_length -= n;
	}
	m_transfer(position, first, last);
}

// relational operators:
template <class T, class Allocator>
bool operator==(const list<T, Allocator> &x, const list<T, Allocator> &y) {
	return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin());
}

template <class T, class Allocator>
bool operator!=(const list<T, Allocator> &x, const list<T, Allocator> &y) {
	return !(x == y);
}

template <class T, class Allocator>
bool operator<(const list<T, Allocator> &x, const list<T, Allocator> &y) {
	return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template <class T, class Allocator>
bool operator>(const list<T, Allocator> &x, const list<T, Allocator> &y) {
	return y < x;
}

template <class T, class Allocator>
bool operator<=(const list<T, Allocator> &x, const list<T, Allocator> &y) {
	return !(y < x);
}

template <class T, class Allocator>
bool operator>=(const list<T, Allocator> &x, const list<T, Allocator> &y) {
	return !(x < y);
}

}  // namespace ft
