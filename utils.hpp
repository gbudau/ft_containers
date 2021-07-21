#pragma once
#include "functional.hpp"

namespace ft {

template <bool flag, class IsTrue, class IsFalse>
struct choose;

template <class IsTrue, class IsFalse>
struct choose<true, IsTrue, IsFalse> {
	typedef IsTrue type;
};

template <class IsTrue, class IsFalse>
struct choose<false, IsTrue, IsFalse> {
	typedef IsFalse type;
};

template <class T, class U>
struct select_first : public unary_function<T, U> {
	const U &operator()(const T &x) const {
		return x.first;
	}
}

}  // namespace ft
