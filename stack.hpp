#pragma once
#include "vector.hpp"

namespace ft {

// https://isocpp.org/wiki/faq/templates#template-friends
template <class T, class Container>
class stack;

template <class T, class Container>
bool operator==(const stack<T, Container> &x, const stack<T, Container> &y);

template <class T, class Container>
bool operator<(const stack<T, Container> &x, const stack<T, Container> &y);

template <class T, class Container = ft::vector<T> >
class stack {
	friend bool operator==
		<> (const stack<T, Container> &x, const stack<T, Container> &y);
	friend bool operator< <> (
		const stack<T, Container> &x, const stack<T, Container> &y);

  public:
	typedef typename Container::value_type value_type;
	typedef typename Container::size_type  size_type;
	typedef Container                      container_type;

  protected:
	Container c;

  public:
	explicit stack(const Container &container = Container()) : c(container) {}

	bool empty() const {
		return c.empty();
	}

	size_type size() const {
		return c.size();
	}

	value_type &top() {
		return c.back();
	}

	const value_type &top() const {
		return c.back();
	}

	void push(const value_type &value) {
		c.push_back(value);
	}

	void pop() {
		c.pop_back();
	}
};

template <class T, class Container>
bool operator==(const stack<T, Container> &x, const stack<T, Container> &y) {
	return x.c == y.c;
}

template <class T, class Container>
bool operator!=(const stack<T, Container> &x, const stack<T, Container> &y) {
	return !(x == y);
}

template <class T, class Container>
bool operator<(const stack<T, Container> &x, const stack<T, Container> &y) {
	return x.c < y.c;
}

template <class T, class Container>
bool operator>(const stack<T, Container> &x, const stack<T, Container> &y) {
	return y < x;
}

template <class T, class Container>
bool operator<=(const stack<T, Container> &x, const stack<T, Container> &y) {
	return !(y < x);
}

template <class T, class Container>
bool operator>=(const stack<T, Container> &x, const stack<T, Container> &y) {
	return !(x < y);
}

}  // namespace ft
