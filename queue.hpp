#pragma once
#include "list.hpp"

namespace ft {

// https://isocpp.org/wiki/faq/templates#template-friends
template <class T, class Container>
class queue;

template <class T, class Container>
bool operator==(const queue<T, Container> &x, const queue<T, Container> &y);

template <class T, class Container>
bool operator<(const queue<T, Container> &x, const queue<T, Container> &y);

template <class T, class Container = ft::list<T> >
class queue {
	friend bool operator==
		<> (const queue<T, Container> &x, const queue<T, Container> &y);
	friend bool operator< <> (
		const queue<T, Container> &x, const queue<T, Container> &y);

  public:
	typedef typename Container::value_type value_type;
	typedef typename Container::size_type  size_type;
	typedef Container                      container_type;

  protected:
	Container c;

  public:
	explicit queue(const Container &container = Container()) : c(container) {}

	bool empty() const {
		return c.empty();
	}

	size_type size() const {
		return c.size();
	}

	value_type &front() {
		return c.front();
	}

	const value_type &front() const {
		return c.front();
	}

	value_type &back() {
		return c.back();
	}

	const value_type &back() const {
		return c.back();
	}

	void push(const value_type &value) {
		c.push_back(value);
	}

	void pop() {
		c.pop_front();
	}
};

template <class T, class Container>
bool operator==(const queue<T, Container> &x, const queue<T, Container> &y) {
	return x.c == y.c;
}

template <class T, class Container>
bool operator!=(const queue<T, Container> &x, const queue<T, Container> &y) {
	return !(x == y);
}

template <class T, class Container>
bool operator<(const queue<T, Container> &x, const queue<T, Container> &y) {
	return x.c < y.c;
}

template <class T, class Container>
bool operator>(const queue<T, Container> &x, const queue<T, Container> &y) {
	return y < x;
}

template <class T, class Container>
bool operator<=(const queue<T, Container> &x, const queue<T, Container> &y) {
	return !(y < x);
}

template <class T, class Container>
bool operator>=(const queue<T, Container> &x, const queue<T, Container> &y) {
	return !(x < y);
}

}  // namespace ft
