#pragma once

namespace ft {

template <bool B, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T> {
	typedef T type;
};

template <class T>
struct remove_const {
	typedef T type;
};

template <class T>
struct remove_const<const T> {
	typedef T type;
};

template <class T, T val>
struct integral_constant {
	typedef integral_constant<T, val> type;
	typedef T                         value_type;
	static const T                    value = val;
									  operator value_type() const {
        return value;
	}
};

template <class T, T val>
T const integral_constant<T, val>::value;

template <bool val>
struct integral_constant<bool, val> {
	typedef integral_constant<bool, val> type;
	typedef bool                         value_type;
	static const bool                    value = val;
										 operator value_type() const {
        return value;
	}
};

template <bool val>
bool const                             integral_constant<bool, val>::value;

typedef integral_constant<bool, true>  true_type;
typedef integral_constant<bool, false> false_type;

template <class T>
struct is_integral : public false_type {};

template <class T>
struct is_integral<const T> : public is_integral<T> {};

template <class T>
struct is_integral<volatile const T> : public is_integral<T> {};

template <class T>
struct is_integral<volatile T> : public is_integral<T> {};

template <>
struct is_integral<unsigned char> : public true_type {};

template <>
struct is_integral<unsigned short> : public true_type {};

template <>
struct is_integral<unsigned int> : public true_type {};

template <>
struct is_integral<unsigned long> : public true_type {};

template <>
struct is_integral<signed char> : public true_type {};

template <>
struct is_integral<short> : public true_type {};

template <>
struct is_integral<int> : public true_type {};

template <>
struct is_integral<long> : public true_type {};

template <>
struct is_integral<char> : public true_type {};

template <>
struct is_integral<bool> : public true_type {};

template <>
struct is_integral<wchar_t> : public true_type {};

}  // namespace ft
