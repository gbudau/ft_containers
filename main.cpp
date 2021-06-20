#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "list.hpp"
#include "vector.hpp"

static int  g_errors;

static void test_condition(const char *function_name, int line_number,
	const char *message, bool condition) {
	if (condition == false) {
		std::cerr << "Error: " << function_name << ": line " << line_number
				  << ": " << message << '\n';
		g_errors++;
	}
}

template <class T>
static void test_values(const char *function_name, int line_number,
	const char *message, const T &a, const T &b) {
	if (a != b) {
		std::cerr << "Error: " << function_name << ": line " << line_number
				  << ": " << message << ": " << a << " != " << b << '\n';
		g_errors++;
	}
}

template <class T>
static void test_values_message(const char *function_name, int line_number,
	const char *message, const T &a, const T &b) {
	if (a != b) {
		std::cerr << "Error: " << function_name << ": line " << line_number
				  << ": " << message << '\n';
		g_errors++;
	}
}

template <class Container1, class Container2>
static void test_equal_size(const Container1 &c1, const Container2 &c2,
	const char *function_name, int line_number) {

	test_values(function_name, line_number, "size", c1.size(), c2.size());
}

template <class Container1, class Container2>
static void test_equal_content(const Container1 &c1, const Container2 &c2,
	const char *function_name, int line_number) {
	typename Container1::const_iterator it1 = c1.begin();
	typename Container2::const_iterator it2 = c2.begin();

	while (it1 != c1.end() && it2 != c2.end()) {
		test_values(function_name, line_number, "value", *it1++, *it2++);
	}
	test_values_message(
		function_name, line_number, "it1 != c1.end()", it1, c1.end());
	test_values_message(
		function_name, line_number, "it2 != c2.end()", it2, c2.end());
}

template <class Container1, class Container2>
static void test_equal_container(const Container1 &c1, const Container2 &c2,
	const char *function_name, int line_number) {
	test_equal_size(c1, c2, function_name, line_number);
	test_equal_content(c1, c2, function_name, line_number);
}

template <class Container1, class Container2>
static void test_container_default_constructor(const Container1 &,
	const Container2 &, const char *function_name, int line_number) {
	Container1 c1;
	Container2 c2;

	test_equal_size(c1, c2, function_name, line_number);
}

template <class Container1, class Container2>
static void test_container_count_constructor(const Container1 &c1,
	const Container2 &c2, const char *function_name, int line_number) {
	test_equal_size(c1, c2, function_name, line_number);
}

template <class T, class Container1, class Container2>
static void test_container_range_constructor(const Container1 &,
	const Container2 &, const T &value, const char *function_name,
	int line_number) {
	Container2 c;

	for (int i = 0; i < 10; i++) {
		c.push_back(value);
	}

	Container1 c_a(c.begin(), c.end());
	Container2 c_b(c.begin(), c.end());
	test_equal_container(c_a, c_b, function_name, line_number);
}

template <class Container1>
static void test_container_copy_constructor(
	const Container1 &c1, const char *function_name, int line_number) {
	Container1 c2(c1);

	test_equal_container(c1, c2, function_name, line_number);
}

template <class Container1>
static void test_container_assignment_operator(
	const Container1 &c1, const char *function_name, int line_number) {
	Container1 c2 = c1;

	test_equal_container(c1, c2, function_name, line_number);
}

template <class Container1, class Container2, typename T>
static void test_container_assign_count(const Container1 &, const Container2 &,
	const T &v, const char *function_name, int line_number) {
	Container1 c1;
	Container2 c2;

	c1.assign(10, v);
	c2.assign(10, v);
	test_equal_container(c1, c2, function_name, line_number);
	c1.assign(5, v);
	c2.assign(5, v);
	test_equal_container(c1, c2, function_name, line_number);
	c1.assign(15, v);
	c2.assign(15, v);
	test_equal_container(c1, c2, function_name, line_number);
}

template <class Container1, class Container2>
static void test_container_assign_range(const Container1 &c1,
	const Container2 &c2, const char *function_name, int line_number) {
	Container1 c_a;
	Container2 c_b;
	c_a.assign(c1.begin(), c1.end());
	c_b.assign(c2.begin(), c2.end());
	test_equal_container(c_a, c_b, function_name, line_number);
	c_a.assign(c1.begin(), c1.begin());
	c_b.assign(c2.begin(), c2.begin());
	test_equal_container(c_a, c_b, function_name, line_number);
}

template <class Container1, class Container2>
static void test_container_get_allocator(const Container1 &c1,
	const Container2 &c2, const char *function_name, int line_number) {
	test_values_message(function_name, line_number,
		"c1.get_allocator() != c2.get_allocator()", c1.get_allocator(),
		c2.get_allocator());
}

template <class Container1, class Container2>
static void test_container_begin(const Container1 &, const Container2 &,
	const char *function_name, int line_number) {
	Container1 c1(5);
	Container2 c2(5);

	test_equal_container(c1, c2, function_name, line_number);
	typename Container1::iterator it1 = c1.begin();
	typename Container2::iterator it2 = c2.begin();
	test_values(function_name, line_number, "iterator", *it1, *it2);

	typename Container1::const_iterator it1c = c1.begin();
	typename Container2::const_iterator it2c = c2.begin();
	test_values(function_name, line_number, "const_iterator", *it1c, *it2c);
}

template <class Container1, class Container2>
static void test_container_end(const Container1 &, const Container2 &,
	const char *function_name, int line_number) {
	Container1 c1(1);
	Container2 c2(1);

	test_equal_container(c1, c2, function_name, line_number);
	typename Container1::iterator it1 = c1.end();
	typename Container2::iterator it2 = c2.end();
	// This works only for the containers that have bidirectional_iterator+
	test_values(function_name, line_number, "iterator", *(--it1), *(--it2));

	typename Container1::const_iterator it1c = c1.end();
	typename Container2::const_iterator it2c = c2.end();
	// This works only for the containers that have bidirectional_iterator+
	test_values(
		function_name, line_number, "const_iterator", *(--it1c), *(--it2c));
}

template <class Container1, class Container2>
static void test_container_rbegin(const Container1 &, const Container2 &,
	const char *function_name, int line_number) {
	Container1 c1(5);
	Container2 c2(5);

	test_equal_container(c1, c2, function_name, line_number);
	typename Container1::reverse_iterator rit1 = c1.rbegin();
	typename Container2::reverse_iterator rit2 = c2.rbegin();
	test_values(function_name, line_number, "reverse_iterator", *rit1, *rit2);

	typename Container1::const_reverse_iterator rit1c = c1.rbegin();
	typename Container2::const_reverse_iterator rit2c = c2.rbegin();
	test_values(
		function_name, line_number, "const_reverse_iterator", *rit1c, *rit2c);
}

template <class Container1, class Container2>
static void test_container_rend(const Container1 &, const Container2 &,
	const char *function_name, int line_number) {
	Container1 c1(1);
	Container2 c2(1);

	test_equal_container(c1, c2, function_name, line_number);
	typename Container1::reverse_iterator rit1 = c1.rend();
	typename Container2::reverse_iterator rit2 = c2.rend();
	// This works only for the containers that have bidirectional_iterator+
	test_values(
		function_name, line_number, "reverse_iterator", *(--rit1), *(--rit2));

	typename Container1::const_reverse_iterator rit1c = c1.rend();
	typename Container2::const_reverse_iterator rit2c = c2.rend();
	// This works only for the containers that have bidirectional_iterator+
	test_values(function_name, line_number, "const_reverse_iterator",
		*(--rit1c), *(--rit2c));
}

template <class Container1, class Container2>
static void test_container_max_size(const Container1 &c1, const Container2 &c2,
	const char *function_name, int line_number) {
	test_values(
		function_name, line_number, "max_size", c1.max_size(), c2.max_size());
}

template <class Container1, class Container2>
static void test_container_resize(const Container1 &c1, const Container2 &c2,
	const char *function_name, int line_number) {
	Container1 c_a(c1);
	Container2 c_b(c2);

	test_equal_container(c_b, c_a, function_name, line_number);
	c_a.resize(5);
	c_b.resize(5);
	test_equal_container(c_b, c_a, function_name, line_number);
	c_a.resize(2);
	c_b.resize(2);
	test_equal_container(c_b, c_a, function_name, line_number);
	c_a.resize(12);
	c_b.resize(12);
	test_equal_container(c_b, c_a, function_name, line_number);
	c_a.resize(c_a.capacity() + 1);
	c_b.resize(c_b.capacity() + 1);
	test_equal_container(c_b, c_a, function_name, line_number);
}

template <class Container1, class Container2>
static void test_container_empty(const Container1 &c1, const Container2 &c2,
	const char *function_name, int line_number) {
	test_values(function_name, line_number, "empty", c1.empty(), c2.empty());
}

template <class Container1, class Container2>
static void test_container_not_empty(const Container1 &c1, const Container2 &c2,
	const char *function_name, int line_number) {
	test_values(function_name, line_number, "empty", c1.empty(), c2.empty());
}

template <class T, class Container1, class Container2>
static void test_container_at(const Container1 &, const Container2 &,
	const T &val, const char *function_name, int line_number) {
	Container1 c1(5);
	Container2 c2(5);

	test_equal_container(c1, c2, function_name, line_number);
	for (std::size_t i = 0; i < c1.size() && i < c2.size(); i++) {
		c1.at(i) = val;
		c2.at(i) = val;
	}
	test_equal_container(c1, c2, function_name, line_number);

	bool a = false;
	bool b = false;
	try {
		c1.at(-1) = val;
	} catch (std::out_of_range const &e) {
		a = true;
	}
	try {
		c2.at(-1) = val;
	} catch (std::out_of_range const &e) {
		b = true;
	}
	test_values(function_name, line_number, "at() exception", a, b);
}

template <class T, class Container1, class Container2>
static void test_container_array_subscript(const Container1 &,
	const Container2 &, const T &val, const char *function_name,
	int line_number) {
	Container1 c1(5);
	Container2 c2(5);

	test_equal_container(c1, c2, function_name, line_number);
	for (std::size_t i = 0; i < c1.size() && i < c2.size(); i++) {
		c1[i] = val;
		c2[i] = val;
	}
	test_equal_container(c1, c2, function_name, line_number);
}

template <class T, class Container1, class Container2>
static void test_container_front(const Container1 &, const Container2 &,
	const T &val, const char *function_name, int line_number) {
	Container1 c1(1);
	Container2 c2(1);

	test_equal_container(c1, c2, function_name, line_number);
	typename Container1::iterator it1 = c1.begin();
	typename Container2::iterator it2 = c2.begin();
	for (; it1 != c1.end() && it2 != c2.end(); it1++, it2++) {
		*it1 = val;
		*it2 = val;
	}
	test_equal_container(c1, c2, function_name, line_number);
	test_values(function_name, line_number, "front", c1.front(), c2.front());
}

template <class T, class Container1, class Container2>
static void test_container_back(const Container1 &, const Container2 &,
	const T &val, const char *function_name, int line_number) {
	Container1 c1(1);
	Container2 c2(1);

	test_equal_container(c1, c2, function_name, line_number);
	typename Container1::iterator it1 = c1.begin();
	typename Container2::iterator it2 = c2.begin();
	for (; it1 != c1.end() && it2 != c2.end(); it1++, it2++) {
		*it1 = val;
		*it2 = val;
	}
	test_equal_container(c1, c2, function_name, line_number);
	test_values(function_name, line_number, "back", c1.back(), c2.back());
}

template <class Container1, class Container2>
static void test_container_reserve(const Container1 &c1, const Container2 &c2,
	const char *function_name, int line_number) {
	Container1 c_a(c1);
	Container2 c_b(c2);

	test_equal_container(c_b, c_a, function_name, line_number);
	c_a.reserve(0);
	c_b.reserve(0);
	test_equal_container(c_b, c_a, function_name, line_number);
	c_a.reserve(c_a.size());
	c_b.reserve(c_b.size());
	test_equal_container(c_b, c_a, function_name, line_number);
	c_a.reserve(c_a.size() * 2);
	c_b.reserve(c_b.size() * 2);
	test_equal_container(c_b, c_a, function_name, line_number);
}

template <class T, class Container1, class Container2>
static void test_container_push_back(const Container1 &, const Container2 &,
	const T &val, const char *function_name, int line_number) {
	Container1 c1;
	Container2 c2;

	test_equal_container(c1, c2, function_name, line_number);
	for (int i = 0; i < 10; i++) {
		c1.push_back(val);
		c2.push_back(val);
		test_equal_container(c1, c2, function_name, line_number);
	}
	test_equal_container(c1, c2, function_name, line_number);
}

template <class Container1, class Container2>
static void test_container_pop_back(const Container1 &, const Container2 &,
	const char *function_name, int line_number) {
	Container1 c1(10);
	Container2 c2(10);

	test_equal_container(c1, c2, function_name, line_number);
	for (std::size_t i = 0; i < c1.size() && i < c2.size(); i++) {
		c1.pop_back();
		c2.pop_back();
		test_equal_container(c1, c2, function_name, line_number);
	}
	test_equal_container(c1, c2, function_name, line_number);
}

template <class T, class Container1, class Container2>
static void test_container_insert_one(const Container1 &, const Container2 &,
	const T &val, const char *function_name, int line_number) {
	Container1 c1;
	Container2 c2;

	test_equal_container(c1, c2, function_name, line_number);
	typename Container1::iterator it1 = c1.insert(c1.end(), val);
	typename Container2::iterator it2 = c2.insert(c2.end(), val);
	test_values(function_name, line_number, "iterator", *it1, *it2);
	test_equal_container(c1, c2, function_name, line_number);
	it1 = c1.insert(c1.begin(), val);
	it2 = c2.insert(c2.begin(), val);
	test_values(function_name, line_number, "iterator", *it1, *it2);
	test_equal_container(c1, c2, function_name, line_number);
}

template <class T, class Container1, class Container2>
static void test_container_insert_count(const Container1 &, const Container2 &,
	const T &val, const char *function_name, int line_number) {
	Container1 c1;
	Container2 c2;

	test_equal_container(c1, c2, function_name, line_number);
	c1.insert(c1.end(), 0, val);
	c2.insert(c2.end(), 0, val);
	test_equal_container(c1, c2, function_name, line_number);
	c1.insert(c1.begin(), 1, val);
	c2.insert(c2.begin(), 1, val);
	test_equal_container(c1, c2, function_name, line_number);
	c1.insert(c1.begin(), 10, val);
	c2.insert(c2.begin(), 10, val);
	test_equal_container(c1, c2, function_name, line_number);
	c1.insert(c1.begin(), 1, val);
	c2.insert(c2.begin(), 1, val);
	test_equal_container(c1, c2, function_name, line_number);
	c1.insert(c1.begin(), 5, val);
	c2.insert(c2.begin(), 5, val);
	test_equal_container(c1, c2, function_name, line_number);
}

template <class Container1, class Container2>
static void test_container_insert_range(const Container1 &, const Container2 &,
	const char *function_name, int line_number) {
	Container1 c1;
	Container2 c2;
	Container1 t1(10);
	Container2 t2(10);

	c1.insert(c1.begin(), t1.begin(), t1.end());
	c2.insert(c2.begin(), t2.begin(), t2.end());
	test_equal_container(c1, c2, function_name, line_number);
	c1.insert(c1.end(), t1.begin(), t1.end());
	c2.insert(c2.end(), t2.begin(), t2.end());
	test_equal_container(c1, c2, function_name, line_number);
	typename Container1::iterator it1 = c1.begin();
	typename Container2::iterator it2 = c2.begin();
	for (std::size_t i = 0; i < c1.size() / 2 && i < c2.size() / 2; i++) {
		it1++;
		it2++;
	}
	c1.insert(it1, t1.begin(), t1.end());
	c2.insert(it2, t2.begin(), t2.end());
	test_equal_container(c1, c2, function_name, line_number);

	Container1 ta(100);
	Container2 tb(100);
	it1 = c1.begin();
	it2 = c2.begin();
	for (std::size_t i = 0; i < c1.size() / 2 && i < c2.size() / 2; i++) {
		it1++;
		it2++;
	}
	c1.insert(it1, ta.begin(), ta.end());
	c2.insert(it2, tb.begin(), tb.end());
	test_equal_container(c1, c2, function_name, line_number);
}

template <class Container1, class Container2>
static void test_container_erase_position(const Container1 &,
	const Container2 &, const char *function_name, int line_number) {
	Container1                    c1(10);
	Container2                    c2(10);
	typename Container1::iterator c1_it;
	typename Container2::iterator c2_it;

	test_equal_container(c1, c2, function_name, line_number);
	for (std::size_t i = 0; i < c1.size(); i++) {
		c1_it = c1.erase(c1.begin());
		c2_it = c2.erase(c2.begin());
		test_values(function_name, line_number, "iterator", *c1_it, *c2_it);
		test_equal_container(c1, c2, function_name, line_number);
	}
	test_equal_container(c1, c2, function_name, line_number);
}

template <class Container1, class Container2>
static void test_container_erase_range(const Container1 &, const Container2 &,
	const char *function_name, int line_number) {
	Container1 c1;
	Container2 c2;

	test_equal_container(c1, c2, function_name, line_number);
	typename Container1::iterator c1_it = c1.erase(c1.begin(), c1.end());
	typename Container2::iterator c2_it = c2.erase(c2.begin(), c2.end());
	test_values_message(
		function_name, line_number, "c1_it != c1.end()", c1_it, c1.end());
	test_values_message(
		function_name, line_number, "c2_it != c2.end()", c2_it, c2.end());
	test_equal_container(c1, c2, function_name, line_number);
	c1 = Container1(5);
	c2 = Container2(5);
	c1_it = c1.erase(c1.begin(), c1.end());
	c2_it = c2.erase(c2.begin(), c2.end());
	test_values_message(
		function_name, line_number, "c1_it != c1_end()", c1_it, c1.end());
	test_values_message(
		function_name, line_number, "c2_it != c2_end()", c2_it, c2.end());
	test_equal_container(c1, c2, function_name, line_number);
}

template <class Container1, class Container2>
static void test_container_swap(const Container1 &, const Container2 &,
	const char *function_name, int line_number) {
	Container1 c1_empty;
	Container2 c2_empty;
	Container1 c1(5);
	Container2 c2(5);

	test_equal_container(c1_empty, c2_empty, function_name, line_number);
	test_equal_container(c1, c2, function_name, line_number);
	c1.swap(c1_empty);
	c2.swap(c2_empty);
	test_equal_container(c1_empty, c2_empty, function_name, line_number);
	test_equal_container(c1, c2, function_name, line_number);
	test_values(function_name, line_number, "size", c1.size(), 0UL);
	test_values(function_name, line_number, "size", c2.size(), 0UL);
	test_values(function_name, line_number, "size", c1_empty.size(), 5UL);
	test_values(function_name, line_number, "size", c2_empty.size(), 5UL);
}

template <class Container1, class Container2>
static void test_container_clear(const Container1 &, const Container2 &,
	const char *function_name, int line_number) {
	Container1 c1;
	Container2 c2;

	test_equal_container(c1, c2, function_name, line_number);
	c1.clear();
	c2.clear();
	test_equal_container(c1, c2, function_name, line_number);
	c1 = Container1(5);
	c2 = Container2(5);
	test_equal_container(c1, c2, function_name, line_number);
	c1.clear();
	c2.clear();
	test_equal_container(c1, c2, function_name, line_number);
}

template <class T, class Container1, class Container2>
static void test_container_equal_operator(const Container1 &,
	const Container2 &, const T &val, const char *function_name,
	int line_number) {
	const int  N = 5;
	Container1 c1a(N);
	Container1 c1b(N);
	Container2 c2a(N);
	Container2 c2b(N);

	for (int i = 0; i < N - 1; i++) {
		c1a[i] = val;
		c1b[i] = val;
		c2a[i] = val;
		c2b[i] = val;
	}
	test_condition(function_name, line_number, "equal operator", c1a == c1b);
	test_condition(function_name, line_number, "equal operator", c2a == c2b);

	c1a[N - 1] = val;
	c2a[N - 1] = val;

	test_condition(function_name, line_number, "equal operator", !(c1a == c1b));
	test_condition(function_name, line_number, "equal operator", !(c2a == c2b));

	Container1 c1;
	Container2 c2;
	test_condition(function_name, line_number, "equal operator", !(c1a == c1));
	test_condition(function_name, line_number, "equal operator", !(c2a == c2));
}

template <class T, class Container1, class Container2>
static void test_container_notequal_operator(const Container1 &,
	const Container2 &, const T &val, const char *function_name,
	int line_number) {
	const int  N = 5;
	Container1 c1a(N);
	Container1 c1b(N);
	Container2 c2a(N);
	Container2 c2b(N);

	for (int i = 0; i < N - 1; i++) {
		c1a[i] = val;
		c1b[i] = val;
		c2a[i] = val;
		c2b[i] = val;
	}
	test_condition(
		function_name, line_number, "notequal operator", !(c1a != c1b));
	test_condition(
		function_name, line_number, "notequal operator", !(c2a != c2b));

	c1a[N - 1] = val;
	c2a[N - 1] = val;

	test_condition(function_name, line_number, "notequal operator", c1a != c1b);
	test_condition(function_name, line_number, "notequal operator", c2a != c2b);

	Container1 c1;
	Container2 c2;
	test_condition(function_name, line_number, "notequal operator", c1a != c1);
	test_condition(function_name, line_number, "notequal operator", c2a != c2);
}

template <class T, class Container1, class Container2>
static void test_container_less_operator(const Container1 &, const Container2 &,
	const T &val_less, const T &val_great, const char *function_name,
	int line_number) {
	Container1 c1a(1, val_less);
	Container1 c1b(1, val_great);
	Container2 c2a(1, val_less);
	Container2 c2b(1, val_great);

	test_condition(function_name, line_number, "less operator", c1a < c1b);
	test_condition(function_name, line_number, "less operator", c2a < c2b);

	Container1 c1_empty;
	Container2 c2_empty;

	test_condition(function_name, line_number, "less operator", c1_empty < c1a);
	test_condition(function_name, line_number, "less operator", c2_empty < c2a);
	test_condition(function_name, line_number, "less operator", !(c1b < c1b));
	test_condition(function_name, line_number, "less operator", !(c2b < c2b));
}

template <class T, class Container1, class Container2>
static void test_container_greater_operator(const Container1 &,
	const Container2 &, const T &val_less, const T &val_great,
	const char *function_name, int line_number) {
	Container1 c1a(1, val_less);
	Container1 c1b(1, val_great);
	Container2 c2a(1, val_less);
	Container2 c2b(1, val_great);

	test_condition(function_name, line_number, "greater operator", c1b > c1a);
	test_condition(function_name, line_number, "greater operator", c2b > c2a);

	Container1 c1_empty;
	Container2 c2_empty;

	test_condition(
		function_name, line_number, "greater operator", c1a > c1_empty);
	test_condition(
		function_name, line_number, "greater operator", c2a > c2_empty);
	test_condition(
		function_name, line_number, "greater operator", !(c1a > c1a));
	test_condition(
		function_name, line_number, "greater operator", !(c2a > c2a));
}

template <class T, class Container1, class Container2>
static void test_container_lessequal_operator(const Container1 &,
	const Container2 &, const T &val_less, const T &val_great,
	const char *function_name, int line_number) {
	Container1 c1a(1, val_less);
	Container1 c1b(1, val_great);
	Container2 c2a(1, val_less);
	Container2 c2b(1, val_great);

	test_condition(
		function_name, line_number, "less-equal operator", c1a <= c1b);
	test_condition(
		function_name, line_number, "less-equal operator", c2a <= c2b);

	Container1 c1_empty;
	Container2 c2_empty;

	test_condition(
		function_name, line_number, "less-equal operator", c1_empty <= c1a);
	test_condition(
		function_name, line_number, "less-equal operator", c2_empty <= c2a);
	test_condition(
		function_name, line_number, "less-equal operator", c1b <= c1b);
	test_condition(
		function_name, line_number, "less-equal operator", c2b <= c2b);
}

template <class T, class Container1, class Container2>
static void test_container_greaterequal_operator(const Container1 &,
	const Container2 &, const T &val_less, const T &val_great,
	const char *function_name, int line_number) {
	Container1 c1a(1, val_less);
	Container1 c1b(1, val_great);
	Container2 c2a(1, val_less);
	Container2 c2b(1, val_great);

	test_condition(
		function_name, line_number, "greater-equal operator", c1b >= c1a);
	test_condition(
		function_name, line_number, "greater-equal operator", c2b >= c2a);

	Container1 c1_empty;
	Container2 c2_empty;

	test_condition(
		function_name, line_number, "greater-equal operator", c1a >= c1_empty);
	test_condition(
		function_name, line_number, "greater-equal operator", c2a >= c2_empty);
	test_condition(
		function_name, line_number, "greater-equal operator", c1b >= c1b);
	test_condition(
		function_name, line_number, "greater-equal operator", c2b >= c2b);
}

template <class Container1, class Container2>
static void test_container_swap_overload(const Container1 &, const Container2 &,
	const char *function_name, int line_number) {
	Container1 c1_empty;
	Container2 c2_empty;
	Container1 c1(5);
	Container2 c2(5);

	test_equal_container(c1_empty, c2_empty, function_name, line_number);
	test_equal_container(c1, c2, function_name, line_number);
	ft::swap(c1, c1_empty);
	std::swap(c2, c2_empty);
	test_equal_container(c1_empty, c2_empty, function_name, line_number);
	test_equal_container(c1, c2, function_name, line_number);
	test_values(function_name, line_number, "size", c1.size(), 0UL);
	test_values(function_name, line_number, "size", c2.size(), 0UL);
	test_values(function_name, line_number, "size", c1_empty.size(), 5UL);
	test_values(function_name, line_number, "size", c2_empty.size(), 5UL);
}

static void test_vector() {
	test_container_default_constructor(
		ft::vector<int>(), std::vector<int>(), __FUNCTION__, __LINE__);
	test_container_count_constructor(
		ft::vector<int>(5), std::vector<int>(5), __FUNCTION__, __LINE__);
	test_container_range_constructor(
		ft::vector<int>(), std::vector<int>(), 111, __FUNCTION__, __LINE__);
	test_container_copy_constructor(
		ft::vector<int>(42), __FUNCTION__, __LINE__);
	test_container_assignment_operator(
		ft::vector<std::string>(1, "hello"), __FUNCTION__, __LINE__);
	test_container_assign_count(
		ft::vector<int>(), std::vector<int>(), 4, __FUNCTION__, __LINE__);
	test_container_assign_range(ft::vector<float>(10, 100.0f),
		std::vector<float>(10, 100.0f), __FUNCTION__, __LINE__);
	test_container_get_allocator(
		ft::vector<char>(), std::vector<char>(), __FUNCTION__, __LINE__);
	test_container_begin(
		ft::vector<double>(), std::vector<double>(), __FUNCTION__, __LINE__);
	test_container_end(ft::vector<std::string>(), std::vector<std::string>(),
		__FUNCTION__, __LINE__);
	test_container_rbegin(
		ft::vector<int>(), std::vector<int>(), __FUNCTION__, __LINE__);
	test_container_rend(
		ft::vector<char>(), std::vector<char>(), __FUNCTION__, __LINE__);
	test_container_max_size(
		ft::vector<int>(), std::vector<int>(), __FUNCTION__, __LINE__);
	test_container_resize(ft::vector<char>(1, 'a'), std::vector<char>(1, 'a'),
		__FUNCTION__, __LINE__);
	test_container_empty(
		ft::vector<int>(), std::vector<int>(), __FUNCTION__, __LINE__);
	test_container_not_empty(
		ft::vector<int>(1, 1), std::vector<int>(1, 1), __FUNCTION__, __LINE__);
	test_container_array_subscript(
		ft::vector<int>(), std::vector<int>(), 1, __FUNCTION__, __LINE__);
	test_container_at(
		ft::vector<int>(), std::vector<int>(), 1, __FUNCTION__, __LINE__);
	test_container_front(
		ft::vector<int>(), std::vector<int>(), 123, __FUNCTION__, __LINE__);
	test_container_back(
		ft::vector<int>(), std::vector<int>(), 123, __FUNCTION__, __LINE__);
	test_container_reserve(ft::vector<int>(10, 42), std::vector<int>(10, 42),
		__FUNCTION__, __LINE__);
	test_container_push_back(
		ft::vector<int>(), std::vector<int>(), 123, __FUNCTION__, __LINE__);
	test_container_pop_back(
		ft::vector<int>(), std::vector<int>(), __FUNCTION__, __LINE__);
	test_container_insert_one(
		ft::vector<int>(), std::vector<int>(), 1, __FUNCTION__, __LINE__);
	test_container_insert_count(
		ft::vector<int>(), std::vector<int>(), 42, __FUNCTION__, __LINE__);
	test_container_insert_range(
		ft::vector<int>(), std::vector<int>(), __FUNCTION__, __LINE__);
	test_container_erase_position(
		ft::vector<int>(), std::vector<int>(), __FUNCTION__, __LINE__);
	test_container_erase_range(
		ft::vector<int>(), std::vector<int>(), __FUNCTION__, __LINE__);
	test_container_swap(
		ft::vector<int>(), std::vector<int>(), __FUNCTION__, __LINE__);
	test_container_clear(
		ft::vector<int>(), std::vector<int>(), __FUNCTION__, __LINE__);
	test_container_equal_operator(
		ft::vector<int>(), std::vector<int>(), 123, __FUNCTION__, __LINE__);
	test_container_notequal_operator(
		ft::vector<int>(), std::vector<int>(), 123, __FUNCTION__, __LINE__);
	test_container_less_operator(ft::vector<std::string>(),
		std::vector<std::string>(), std::string("abcd"), std::string("bcde"),
		__FUNCTION__, __LINE__);
	test_container_greater_operator(ft::vector<std::string>(),
		std::vector<std::string>(), std::string("abcd"), std::string("bcde"),
		__FUNCTION__, __LINE__);
	test_container_lessequal_operator(ft::vector<std::string>(),
		std::vector<std::string>(), std::string("abcd"), std::string("bcde"),
		__FUNCTION__, __LINE__);
	test_container_greaterequal_operator(ft::vector<std::string>(),
		std::vector<std::string>(), std::string("abcd"), std::string("bcde"),
		__FUNCTION__, __LINE__);
	test_container_swap_overload(
		ft::vector<int>(), std::vector<int>(), __FUNCTION__, __LINE__);
}

static void test_list() {
	test_container_default_constructor(
		ft::list<int>(), std::list<int>(), __FUNCTION__, __LINE__);
	test_container_count_constructor(
		ft::list<int>(5), std::list<int>(5), __FUNCTION__, __LINE__);
	test_container_range_constructor(
		ft::list<int>(), std::list<int>(), 111, __FUNCTION__, __LINE__);
	test_container_copy_constructor(ft::list<int>(42), __FUNCTION__, __LINE__);
}

int main() {
	test_vector();
	test_list();
	std::cout << g_errors << " errors\n";
	return g_errors ? 1 : 0;
}
