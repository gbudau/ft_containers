#include <cstdlib>
#include <ctime>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include "list.hpp"
#include "map.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include "utility.hpp"
#include "vector.hpp"

static int g_errors;

template <class Container>
void print_container(const Container &c) {
	typename Container::const_iterator it = c.begin();
	typename Container::const_iterator ite = c.end();

	std::cout << "Container content: ";
	while (it != ite) {
		std::cout << *it++ << ' ';
	}
	std::cout << '\n';
}

template <class T>
bool is_even(const T n) {
	return n % 2;
}

template <class T>
bool both_numbers_are_even(const T a, const T b) {
	return is_even(a) && is_even(b);
}

char generateRandomChar() {
	return std::rand() % 128;
}

std::string generateRandomString() {
	std::string str;
	int         length = std::rand() % 65;

	str.reserve(length);
	for (int i = 0; i < length; i++) {
		str[i] = generateRandomChar();
	}
	return str;
}

template <class T, class Container1, class Container2>
void add_random_values_to_containers(
	Container1 &c1, Container2 &c2, T (*generateRandomValue)(), int N) {
	for (int i = 0; i < N; i++) {
		T value = generateRandomValue();
		c1.push_back(value);
		c2.push_back(value);
	}
}

template <class T, class Container1, class Container2>
void add_random_values_to_containers_adaptors(
	Container1 &c1, Container2 &c2, T (*generateRandomValue)(), int N) {
	for (int i = 0; i < N; i++) {
		T value = generateRandomValue();
		c1.push(value);
		c2.push(value);
	}
}

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

	test_equal_container(c1, c2, function_name, line_number);
}

template <class Container1, class Container2>
static void test_container_adaptor_default_constructor(const Container1 &,
	const Container2 &, const char *function_name, int line_number) {
	Container1 c1;
	Container2 c2;

	test_equal_size(c1, c2, function_name, line_number);
}

template <class Value1, class Value2>
static void test_map_values(const char *message, const Value1 &value1,
	const Value2 &value2, const char *function_name, int line_number) {
	if (value1.first != value2.first) {
		std::cerr << "Error: " << function_name << ": line " << line_number
				  << ": " << message << ": " << value1.first
				  << " != " << value2.first << '\n';
		g_errors++;
	}
	if (value1.second != value2.second) {
		std::cerr << "Error: " << function_name << ": line " << line_number
				  << ": " << message << ": " << value1.second
				  << " != " << value2.second << '\n';
		g_errors++;
	}
}

template <class Map1, class Map2>
static void test_equal_content_map(const Map1 &c1, const Map2 &c2,
	const char *function_name, int line_number) {
	typename Map1::const_iterator it1 = c1.begin();
	typename Map2::const_iterator it2 = c2.begin();

	while (it1 != c1.end() && it2 != c2.end()) {
		test_map_values("value", *it1++, *it2++, function_name, line_number);
	}
	test_values_message(
		function_name, line_number, "it1 != c1.end()", it1, c1.end());
	test_values_message(
		function_name, line_number, "it2 != c2.end()", it2, c2.end());
}

template <class Map1, class Map2>
static void test_equal_map_container(const Map1 &m1, const Map2 &m2,
	const char *function_name, int line_number) {

	test_equal_size(m1, m2, function_name, line_number);
	test_equal_content_map(m1, m2, function_name, line_number);
}

template <class Map1, class Map2>
static void test_map_default_constructor(
	const Map1 &, const Map2 &, const char *function_name, int line_number) {
	Map1 m1;
	Map2 m2;

	test_equal_size(m1, m2, function_name, line_number);
}

template <class Map1, class Value1, class Map2, class Value2, class Key,
	class MappedType>
static void test_map_range_constructor(const Map1 &, const Value1 &,
	const Map2 &, const Value2 &, Key (*generateRandomKey)(),
	MappedType (*generateRandomMappedType)(), const char *function_name,
	int line_number) {

	const int           size = 100;
	std::vector<Value1> vec1;
	std::vector<Value2> vec2;

	for (int i = 0; i < size; ++i) {
		Key        key = generateRandomKey();
		MappedType mapped_type = generateRandomMappedType();
		Value1     value1 = Value1(key, mapped_type);
		Value2     value2 = Value2(key, mapped_type);
		vec1.push_back(value1);
		vec2.push_back(value2);
	}
	Map1 m1(vec1.begin(), vec1.end());
	Map2 m2(vec2.begin(), vec2.end());
	test_equal_map_container(m1, m2, function_name, line_number);
}

template <class Map1, class Value1, class Map2, class Value2, class Key,
	class MappedType>
static void add_random_map_values(Map1 &map1, const Value1 &, Map2 &map2,
	const Value2 &, Key (*generateRandomKey)(),
	MappedType (*generateRandomMappedType)(), std::size_t n) {
	while (n--) {
		Key        key = generateRandomKey();
		MappedType mapped_type = generateRandomMappedType();
		Value1     value1 = Value1(key, mapped_type);
		map1.insert(value1);
		Value2 value2 = Value2(key, mapped_type);
		map2.insert(value2);
	}
}

template <class Map1, class Value1, class Map2, class Value2, class Key,
	class MappedType>
static void test_map_copy_constructor(const Map1 &, const Value1 &,
	const Map2 &, const Value2 &, Key (*generateRandomKey)(),
	MappedType (*generateRandomMappedType)(), const char *function_name,
	int line_number) {

	Map1 m1;
	Map2 m2;

	add_random_map_values(m1, Value1(), m2, Value2(), generateRandomKey,
		generateRandomMappedType, 30);
	test_equal_map_container(m1, m2, function_name, line_number);
}

template <class Map1, class Value1, class Map2, class Value2, class Key,
	class MappedType>
static void test_map_assignment_operator(const Map1 &, const Value1 &,
	const Map2 &, const Value2 &, Key (*generateRandomKey)(),
	MappedType (*generateRandomMappedType)(), const char *function_name,
	int line_number) {

	Map1 m1;
	Map2 m2;

	add_random_map_values(m1, Value1(), m2, Value2(), generateRandomKey,
		generateRandomMappedType, 30);
	test_equal_map_container(m1, m2, function_name, line_number);

	Map1 m1_copy;
	Map2 m2_copy;

	m1_copy = m1;
	m2_copy = m2;
	test_equal_map_container(m1_copy, m2_copy, function_name, line_number);
}

template <class Map1, class Value1, class Map2, class Value2, class Key,
	class MappedType>
static void test_map_begin(const Map1 &, const Value1 &, const Map2 &,
	const Value2 &, Key (*generateRandomKey)(),
	MappedType (*generateRandomMappedType)(), const char *function_name,
	int line_number) {

	Map1 m1;
	Map2 m2;

	add_random_map_values(m1, Value1(), m2, Value2(), generateRandomKey,
		generateRandomMappedType, 30);
	test_equal_map_container(m1, m2, function_name, line_number);
	typename Map1::iterator it1 = m1.begin();
	typename Map2::iterator it2 = m2.begin();
	test_map_values("iterator", *it1, *it2, function_name, line_number);

	typename Map1::const_iterator it1c = m1.begin();
	typename Map2::const_iterator it2c = m2.begin();
	test_map_values("const_iterator", *it1c, *it2c, function_name, line_number);
}

template <class Map1, class Value1, class Map2, class Value2, class Key,
	class MappedType>
static void test_map_end(const Map1 &, const Value1 &, const Map2 &,
	const Value2 &, Key (*generateRandomKey)(),
	MappedType (*generateRandomMappedType)(), const char *function_name,
	int line_number) {

	Map1 m1;
	Map2 m2;

	add_random_map_values(m1, Value1(), m2, Value2(), generateRandomKey,
		generateRandomMappedType, 30);
	test_equal_map_container(m1, m2, function_name, line_number);
	typename Map1::iterator it1 = m1.end();
	typename Map2::iterator it2 = m2.end();
	test_map_values("iterator", *(--it1), *(--it2), function_name, line_number);

	typename Map1::const_iterator it1c = m1.end();
	typename Map2::const_iterator it2c = m2.end();
	test_map_values(
		"const_iterator", *(--it1c), *(--it2c), function_name, line_number);
}

template <class Map1, class Value1, class Map2, class Value2, class Key,
	class MappedType>
static void test_map_rbegin(const Map1 &, const Value1 &, const Map2 &,
	const Value2 &, Key (*generateRandomKey)(),
	MappedType (*generateRandomMappedType)(), const char *function_name,
	int line_number) {

	Map1 m1;
	Map2 m2;

	add_random_map_values(m1, Value1(), m2, Value2(), generateRandomKey,
		generateRandomMappedType, 30);
	test_equal_map_container(m1, m2, function_name, line_number);
	typename Map1::reverse_iterator rit1 = m1.rbegin();
	typename Map2::reverse_iterator rit2 = m2.rbegin();
	test_map_values("iterator", *rit1, *rit2, function_name, line_number);

	typename Map1::const_reverse_iterator rit1c = m1.rbegin();
	typename Map2::const_reverse_iterator rit2c = m2.rbegin();
	test_map_values(
		"const_reverse_iterator", *rit1c, *rit2c, function_name, line_number);
}

template <class Map1, class Value1, class Map2, class Value2, class Key,
	class MappedType>
static void test_map_rend(const Map1 &, const Value1 &, const Map2 &,
	const Value2 &, Key (*generateRandomKey)(),
	MappedType (*generateRandomMappedType)(), const char *function_name,
	int line_number) {

	Map1 m1;
	Map2 m2;

	add_random_map_values(m1, Value1(), m2, Value2(), generateRandomKey,
		generateRandomMappedType, 30);
	test_equal_map_container(m1, m2, function_name, line_number);
	typename Map1::reverse_iterator rit1 = m1.rend();
	typename Map2::reverse_iterator rit2 = m2.rend();
	test_map_values(
		"iterator", *(--rit1), *(--rit2), function_name, line_number);

	typename Map1::const_reverse_iterator rit1c = m1.rend();
	typename Map2::const_reverse_iterator rit2c = m2.rend();
	test_map_values(
		"const_iterator", *(--rit1c), *(--rit2c), function_name, line_number);
}

template <class Map1, class Value1, class Map2, class Value2, class Key,
	class MappedType>
static void test_map_empty(const Map1 &, const Value1 &, const Map2 &,
	const Value2 &, Key (*generateRandomKey)(),
	MappedType (*generateRandomMappedType)(), const char *function_name,
	int line_number) {

	Map1 m1;
	Map2 m2;

	test_equal_map_container(m1, m2, function_name, line_number);
	test_values_message(function_name, line_number, "m1.empty() != m2.empty()",
		m1.empty(), m2.empty());
	add_random_map_values(m1, Value1(), m2, Value2(), generateRandomKey,
		generateRandomMappedType, 30);
	test_equal_map_container(m1, m2, function_name, line_number);
	test_values_message(function_name, line_number, "m1.empty() != m2.empty()",
		m1.empty(), m2.empty());
}

template <class Map1, class Value1, class Map2, class Value2, class Key,
	class MappedType>
static void test_map_element_access(const Map1 &, const Value1 &, const Map2 &,
	const Value2 &, Key (*generateRandomKey)(),
	MappedType (*generateRandomMappedType)(), const char *function_name,
	int line_number) {

	Map1 m1;
	Map2 m2;

	test_equal_map_container(m1, m2, function_name, line_number);
	Key key = generateRandomKey();
	test_values_message(
		function_name, line_number, "operator[]", m1[key], m2[key]);
	MappedType mapped_type = generateRandomMappedType();
	m1[key] = mapped_type;
	m2[key] = mapped_type;
	test_values_message(
		function_name, line_number, "operator[]", m1[key], m2[key]);
	test_equal_map_container(m1, m2, function_name, line_number);
}

template <class Container1, class Container2>
static void test_container_count_constructor(const Container1 &,
	const Container2 &, const char *function_name, int line_number) {
	Container1 c1(10);
	Container2 c2(10);
	test_equal_container(c1, c2, function_name, line_number);
}

template <class T, class Container1, class Container2>
static void test_container_range_constructor(const Container1 &,
	const Container2 &, T (*generateRandomValue)(), const char *function_name,
	int line_number) {
	std::vector<T> v;

	for (int i = 0; i < 10; i++) {
		T value = generateRandomValue();
		v.push_back(value);
	}

	Container1 c1(v.begin(), v.end());
	Container2 c2(v.begin(), v.end());
	test_equal_container(c1, c2, function_name, line_number);
}

template <class Container>
static void test_container_copy_constructor(
	const Container &c1, const char *function_name, int line_number) {
	Container c2(c1);

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
	c_a.resize(c_a.size() + 1);
	c_b.resize(c_b.size() + 1);
	test_equal_container(c_b, c_a, function_name, line_number);
}

template <class Container1, class Container2>
static void test_container_empty(const Container1 &c1, const Container2 &c2,
	const char *function_name, int line_number) {
	test_values(function_name, line_number, "empty", c1.empty(), c2.empty());
}

template <class Container1, class Container2, class T>
static void test_container_adaptor_empty(const Container1 &, const Container2 &,
	T (*generateRandomValue)(), const char *function_name, int line_number) {
	Container1 c1;
	Container2 c2;

	test_values(function_name, line_number, "empty", c1.empty(), c2.empty());
	add_random_values_to_containers_adaptors(c1, c2, generateRandomValue, 10);
	test_values(function_name, line_number, "empty", c1.empty(), c2.empty());
}

template <class Container1, class Container2, class T>
static void test_container_adaptor_size(const Container1 &, const Container2 &,
	T (*generateRandomValue)(), const char *function_name, int line_number) {

	Container1 c1;
	Container2 c2;

	test_values(function_name, line_number, "size", c1.size(), c2.size());
	add_random_values_to_containers_adaptors(c1, c2, generateRandomValue, 10);
	test_values(function_name, line_number, "size", c1.size(), c2.size());
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

template <class Container1, class Container2, class T>
static void test_container_adaptor_front(const Container1 &, const Container2 &,
	T (*generateRandomValue)(), const char *function_name, int line_number) {
	Container1 c1;
	Container2 c2;

	add_random_values_to_containers_adaptors(c1, c2, generateRandomValue, 2);
	test_values(function_name, line_number, "front", c1.front(), c2.front());

	const Container1 c1_const(c1);
	const Container2 c2_const(c2);
	test_values(
		function_name, line_number, "const front", c1.front(), c2.front());
}

template <class Container1, class Container2, class T>
static void test_container_adaptor_top(const Container1 &, const Container2 &,
	T (*generateRandomValue)(), const char *function_name, int line_number) {
	Container1 c1;
	Container2 c2;

	add_random_values_to_containers_adaptors(c1, c2, generateRandomValue, 2);
	test_values(function_name, line_number, "top", c1.top(), c2.top());

	const Container1 c1_const(c1);
	const Container2 c2_const(c2);
	test_values(function_name, line_number, "const top", c1.top(), c2.top());
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

template <class Container1, class Container2, class T>
static void test_container_adaptor_back(const Container1 &, const Container2 &,
	T (*generateRandomValue)(), const char *function_name, int line_number) {
	Container1 c1;
	Container2 c2;

	add_random_values_to_containers_adaptors(c1, c2, generateRandomValue, 2);
	test_values(function_name, line_number, "back", c1.back(), c2.back());

	const Container1 c1_const(c1);
	const Container2 c2_const(c2);
	test_values(function_name, line_number, "const back", c1.back(), c2.back());
}

template <class QueueContainer1, class QueueContainer2, class T>
static void test_queue_push(const QueueContainer1 &, const QueueContainer2 &,
	T (*generateRandomValue)(), const char *function_name, int line_number) {
	QueueContainer1 c1;
	QueueContainer2 c2;

	for (int i = 0; i < 10; ++i) {
		T value = generateRandomValue();
		c1.push(value);
		c2.push(value);
		test_values(function_name, line_number, "size", c1.size(), c2.size());
		test_values(
			function_name, line_number, "front", c1.front(), c2.front());
		test_values(function_name, line_number, "back", c1.back(), c2.back());
	}
}

template <class StackContainer1, class StackContainer2, class T>
static void test_stack_push(const StackContainer1 &, const StackContainer2 &,
	T (*generateRandomValue)(), const char *function_name, int line_number) {
	StackContainer1 c1;
	StackContainer2 c2;

	for (int i = 0; i < 10; ++i) {
		T value = generateRandomValue();
		c1.push(value);
		c2.push(value);
		test_values(function_name, line_number, "size", c1.size(), c2.size());
		test_values(function_name, line_number, "top", c1.top(), c2.top());
	}
}

template <class QueueContainer1, class QueueContainer2, class T>
static void test_queue_pop(const QueueContainer1 &, const QueueContainer2 &,
	T (*generateRandomValue)(), const char *function_name, int line_number) {
	QueueContainer1 c1;
	QueueContainer2 c2;

	add_random_values_to_containers_adaptors(c1, c2, generateRandomValue, 10);
	while (!c1.empty() && c2.empty()) {
		c1.pop();
		c2.pop();
		test_values(function_name, line_number, "size", c1.size(), c2.size());
		test_values(
			function_name, line_number, "front", c1.front(), c2.front());
		test_values(function_name, line_number, "back", c1.back(), c2.back());
	}
	test_values(function_name, line_number, "size", c1.size(), c2.size());
}

template <class StackContainer1, class StackContainer2, class T>
static void test_stack_pop(const StackContainer1 &, const StackContainer2 &,
	T (*generateRandomValue)(), const char *function_name, int line_number) {
	StackContainer1 c1;
	StackContainer2 c2;

	add_random_values_to_containers_adaptors(c1, c2, generateRandomValue, 10);
	while (!c1.empty() && c2.empty()) {
		c1.pop();
		c2.pop();
		test_values(function_name, line_number, "size", c1.size(), c2.size());
		test_values(function_name, line_number, "top", c1.top(), c2.top());
	}
	test_values(function_name, line_number, "size", c1.size(), c2.size());
}

template <class Container, class T>
static void test_container_adaptor_comparison_operators(const Container &,
	T (*generateRandomValue)(), const char *function_name, int line_number) {
	Container c1a;
	Container c1b;

	add_random_values_to_containers_adaptors(c1a, c1b, generateRandomValue, 5);
	test_condition(function_name, line_number, "equal operator", c1a == c1b);
	test_condition(
		function_name, line_number, "less than or equal operator", c1a <= c1b);
	test_condition(
		function_name, line_number, "greater than or operator", c1a >= c1b);
	add_random_values_to_containers_adaptors(c1b, c1b, generateRandomValue, 1);
	test_condition(
		function_name, line_number, "not equal operator", c1a != c1b);
	test_condition(function_name, line_number, "less than operator", c1a < c1b);
	test_condition(
		function_name, line_number, "greater than operator", c1b > c1a);
	test_condition(
		function_name, line_number, "less than or equal operator", c1a <= c1b);
	test_condition(
		function_name, line_number, "greater than or operator", c1b >= c1a);
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
static void test_container_push_front(const Container1 &, const Container2 &,
	const T &val, const char *function_name, int line_number) {
	Container1 c1;
	Container2 c2;

	test_equal_container(c1, c2, function_name, line_number);
	for (int i = 0; i < 10; i++) {
		c1.push_front(val);
		c2.push_front(val);
		test_equal_container(c1, c2, function_name, line_number);
	}
	test_equal_container(c1, c2, function_name, line_number);
}

template <class Container1, class Container2>
static void test_container_pop_front(const Container1 &, const Container2 &,
	const char *function_name, int line_number) {
	Container1 c1(10);
	Container2 c2(10);

	test_equal_container(c1, c2, function_name, line_number);
	for (std::size_t i = 0; i < c1.size() && i < c2.size(); i++) {
		c1.pop_front();
		c2.pop_front();
		test_equal_container(c1, c2, function_name, line_number);
	}
	test_equal_container(c1, c2, function_name, line_number);
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

template <class Container1, class Container2, class T>
static void test_container_erase_position(const Container1 &,
	const Container2 &, T (*generateRandomValue)(), const char *function_name,
	int line_number) {
	Container1                    c1;
	Container2                    c2;
	typename Container1::iterator c1_it;
	typename Container2::iterator c2_it;

	add_random_values_to_containers(c1, c2, generateRandomValue, 10);
	test_equal_container(c1, c2, function_name, line_number);
	for (std::size_t i = 0; i < c1.size(); i++) {
		c1_it = c1.erase(c1.begin());
		c2_it = c2.erase(c2.begin());
		test_values(function_name, line_number, "iterator", *c1_it, *c2_it);
		test_equal_container(c1, c2, function_name, line_number);
	}
	test_equal_container(c1, c2, function_name, line_number);
}

template <class Container1, class Container2, class T>
static void test_container_erase_range(const Container1 &, const Container2 &,
	T (*generateRandomValue)(), const char *function_name, int line_number) {
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
	add_random_values_to_containers(c1, c2, generateRandomValue, 10);
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
	Container1 c1a;
	Container1 c1b;
	Container2 c2a;
	Container2 c2b;

	for (int i = 0; i < N; i++) {
		c1a.push_back(val);
		c1b.push_back(val);
		c2a.push_back(val);
		c2b.push_back(val);
	}
	test_condition(function_name, line_number, "equal operator", c1a == c1b);
	test_condition(function_name, line_number, "equal operator", c2a == c2b);

	c1a.push_back(val);
	c2a.push_back(val);

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
	Container1 c1a;
	Container1 c1b;
	Container2 c2a;
	Container2 c2b;

	for (int i = 0; i < N - 1; i++) {
		c1a.push_back(val);
		c1b.push_back(val);
		c2a.push_back(val);
		c2b.push_back(val);
	}
	test_condition(
		function_name, line_number, "notequal operator", !(c1a != c1b));
	test_condition(
		function_name, line_number, "notequal operator", !(c2a != c2b));

	c1a.push_back(val);
	c2a.push_back(val);

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

template <class Container1, class Container2, class T>
static void test_list_splice_entire_list(const Container1 &, const Container2 &,
	T (*generateRandomValue)(), const char *function_name, int line_number) {
	Container1 c1_empty;
	Container2 c2_empty;
	Container1 c1;
	Container2 c2;

	add_random_values_to_containers(c1, c2, generateRandomValue, 10);
	test_equal_container(c1_empty, c2_empty, function_name, line_number);
	test_equal_container(c1, c2, function_name, line_number);
	c1_empty.splice(c1_empty.begin(), c1);
	c2_empty.splice(c2_empty.begin(), c2);
	test_equal_container(c1_empty, c2_empty, function_name, line_number);
	test_equal_container(c1, c2, function_name, line_number);

	Container1 c1a;
	Container2 c2a;
	add_random_values_to_containers(c1a, c2a, generateRandomValue, 10);
	c1_empty.splice(c1_empty.end(), c1a);
	c2_empty.splice(c2_empty.end(), c2a);
	test_equal_container(c1_empty, c2_empty, function_name, line_number);
	test_equal_container(c1a, c2a, function_name, line_number);
}

template <class Container1, class Container2, class T>
static void test_list_splice_one_iterator(const Container1 &,
	const Container2 &, T (*generateRandomValue)(), const char *function_name,
	int line_number) {
	Container1 c1_empty;
	Container2 c2_empty;
	Container1 c1;
	Container2 c2;

	add_random_values_to_containers(c1, c2, generateRandomValue, 10);
	test_equal_container(c1_empty, c2_empty, function_name, line_number);
	test_equal_container(c1, c2, function_name, line_number);
	c1_empty.splice(c1_empty.begin(), c1, c1.begin());
	c2_empty.splice(c2_empty.begin(), c2, c2.begin());
	test_equal_container(c1_empty, c2_empty, function_name, line_number);
	test_equal_container(c1, c2, function_name, line_number);
	c1_empty.splice(c1_empty.begin(), c1, ft::prev(c1.end()));
	c2_empty.splice(c2_empty.begin(), c2, ft::prev(c2.end()));
	test_equal_container(c1_empty, c2_empty, function_name, line_number);
	test_equal_container(c1, c2, function_name, line_number);
	c1.splice(c1.begin(), c1, c1.begin());
	c2.splice(c2.begin(), c2, c2.begin());
	test_equal_container(c1, c2, function_name, line_number);
	c1.splice(c1.end(), c1, ft::prev(c1.end()));
	c2.splice(c2.end(), c2, ft::prev(c2.end()));
	test_equal_container(c1, c2, function_name, line_number);
}

template <class Container1, class Container2, class T>
static void test_list_splice_range(const Container1 &, const Container2 &,
	T (*generateRandomValue)(), const char *function_name, int line_number) {
	Container1 c1_empty;
	Container2 c2_empty;
	Container1 c1;
	Container2 c2;

	add_random_values_to_containers(c1, c2, generateRandomValue, 10);
	test_equal_container(c1_empty, c2_empty, function_name, line_number);
	test_equal_container(c1, c2, function_name, line_number);
	c1.splice(c1.begin(), c1, ft::next(c1.begin()), c1.end());
	c2.splice(c2.begin(), c2, ft::next(c2.begin()), c2.end());
	test_equal_container(c1, c2, function_name, line_number);
	c1.splice(c1.end(), c1, c1.begin(), c1.end());
	c2.splice(c2.end(), c2, c2.begin(), c2.end());
	test_equal_container(c1, c2, function_name, line_number);
	c1_empty.splice(c1_empty.begin(), c1, c1.begin(), c1.end());
	c2_empty.splice(c2_empty.begin(), c2, c2.begin(), c2.end());
	test_equal_container(c1_empty, c2_empty, function_name, line_number);
	test_equal_container(c1, c2, function_name, line_number);
	c1_empty.splice(c1_empty.end(), c1_empty, c1_empty.begin(), c1_empty.end());
	c2_empty.splice(c2_empty.end(), c2_empty, c2_empty.begin(), c2_empty.end());
}

template <class Container1, class Container2, class T>
static void test_list_remove(const Container1 &, const Container2 &,
	T (*generateRandomValue)(), const char *function_name, int line_number) {
	Container1 c1;
	Container2 c2;

	add_random_values_to_containers(c1, c2, generateRandomValue, 10);
	test_equal_container(c1, c2, function_name, line_number);
	T value1 = c1.front();
	T value2 = c2.front();
	c1.remove(value1);
	c2.remove(value2);
	test_equal_container(c1, c2, function_name, line_number);
	value1 = c1.back();
	value2 = c2.back();
	c1.remove(value1);
	c2.remove(value2);
	test_equal_container(c1, c2, function_name, line_number);
	T value = generateRandomValue();
	c1.remove(value);
	c2.remove(value);
	test_equal_container(c1, c2, function_name, line_number);
}

template <class Container1, class Container2, class T>
static void test_list_remove_if(const Container1 &, const Container2 &,
	T (*generateRandomValue)(), bool (*funcPtr)(T), const char *function_name,
	int line_number) {
	Container1 c1;
	Container2 c2;

	add_random_values_to_containers(c1, c2, generateRandomValue, 10);
	test_equal_container(c1, c2, function_name, line_number);
	c1.remove_if(funcPtr);
	c2.remove_if(funcPtr);
	test_equal_container(c1, c2, function_name, line_number);
}

template <class Container1, class Container2, class T>
static void test_list_unique(const Container1 &, const Container2 &,
	T (*generateRandomValue)(), const char *function_name, int line_number) {
	T          value = generateRandomValue();
	Container1 c1(10, value);
	Container2 c2(10, value);

	test_equal_container(c1, c2, function_name, line_number);
	c1.unique();
	c2.unique();
	test_equal_container(c1, c2, function_name, line_number);
	add_random_values_to_containers(c1, c2, generateRandomValue, 100);
	c1.unique();
	c2.unique();
	test_equal_container(c1, c2, function_name, line_number);

	Container1 c1_one(1);
	Container1 c2_one(1);
	c1_one.unique();
	c2_one.unique();
	test_equal_container(c1_one, c2_one, function_name, line_number);
}

template <class Container1, class Container2, class T>
static void test_list_unique_predicate(const Container1 &, const Container2 &,
	T (*generateRandomValue)(), bool (*funcPtr)(T, T),
	const char *function_name, int line_number) {
	Container1 c1;
	Container2 c2;

	add_random_values_to_containers(c1, c2, generateRandomValue, 20);
	test_equal_container(c1, c2, function_name, line_number);
	c1.unique(funcPtr);
	c2.unique(funcPtr);
	test_equal_container(c1, c2, function_name, line_number);

	Container1 c1_one(1);
	Container1 c2_one(1);
	c1_one.unique(funcPtr);
	c2_one.unique(funcPtr);
	test_equal_container(c1_one, c2_one, function_name, line_number);
}

template <class Container1, class Container2, class T>
static void test_list_merge(const Container1 &, const Container2 &,
	T (*generateRandomValue)(), const char *function_name, int line_number) {
	Container1 c1a;
	Container1 c1b;
	Container2 c2a;
	Container2 c2b;

	add_random_values_to_containers(c1a, c2a, generateRandomValue, 10);
	test_equal_container(c1a, c2a, function_name, line_number);
	add_random_values_to_containers(c1b, c2b, generateRandomValue, 10);
	test_equal_container(c1b, c2b, function_name, line_number);
	c1a.merge(c1b);
	c2a.merge(c2b);
	test_equal_container(c1a, c2a, function_name, line_number);
	test_equal_container(c1b, c2b, function_name, line_number);
}

template <class Container1, class Container2, class T, class Compare>
static void test_list_merge_compare(const Container1 &, const Container2 &,
	T (*generateRandomValue)(), Compare comp, const char *function_name,
	int line_number) {
	Container1 c1a;
	Container1 c1b;
	Container2 c2a;
	Container2 c2b;

	add_random_values_to_containers(c1a, c2a, generateRandomValue, 10);
	test_equal_container(c1a, c2a, function_name, line_number);
	add_random_values_to_containers(c1b, c2b, generateRandomValue, 10);
	test_equal_container(c1b, c2b, function_name, line_number);
	c1a.merge(c1b, comp);
	c2a.merge(c2b, comp);
	test_equal_container(c1a, c2a, function_name, line_number);
	test_equal_container(c1b, c2b, function_name, line_number);
}

template <class Container1, class Container2, class T>
static void test_list_reverse(const Container1 &, const Container2 &,
	T (*generateRandomValue)(), const char *function_name, int line_number) {
	Container1 c1;
	Container2 c2;

	add_random_values_to_containers(c1, c2, generateRandomValue, 10);
	test_equal_container(c1, c2, function_name, line_number);
	c1.reverse();
	c2.reverse();
	test_equal_container(c1, c2, function_name, line_number);
	c1.reverse();
	c2.reverse();
	test_equal_container(c1, c2, function_name, line_number);
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

template <class Container1, class Container2, class T>
static void test_container_sort(const Container1 &, const Container2 &,
	T (*generateRandomValue)(), const char *function_name, int line_number) {
	Container1 c1;
	Container2 c2;

	for (int i = 0; i < 5; ++i) {
		add_random_values_to_containers(c1, c2, generateRandomValue, i);
		c1.sort();
		c2.sort();
		test_equal_container(c1, c2, function_name, line_number);
	}
}

template <class Container1, class Container2, class T, class Compare>
static void test_container_sort_compare(const Container1 &, const Container2 &,
	T (*generateRandomValue)(), Compare comp, const char *function_name,
	int line_number) {
	Container1 c1;
	Container2 c2;

	for (int i = 0; i < 5; ++i) {
		add_random_values_to_containers(c1, c2, generateRandomValue, i);
		c1.sort(comp);
		c2.sort(comp);
		test_equal_container(c1, c2, function_name, line_number);
	}
}

static void test_vector() {
	test_container_default_constructor(
		ft::vector<int>(), std::vector<int>(), __FUNCTION__, __LINE__);
	test_container_count_constructor(
		ft::vector<int>(), std::vector<int>(), __FUNCTION__, __LINE__);
	test_container_range_constructor(ft::vector<int>(), std::vector<int>(),
		std::rand, __FUNCTION__, __LINE__);
	test_container_copy_constructor(ft::vector<int>(5), __FUNCTION__, __LINE__);
	test_container_assignment_operator(
		ft::vector<std::string>(10), __FUNCTION__, __LINE__);
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
	test_container_erase_position(ft::vector<int>(), std::vector<int>(),
		std::rand, __FUNCTION__, __LINE__);
	test_container_erase_range(ft::vector<int>(), std::vector<int>(), std::rand,
		__FUNCTION__, __LINE__);
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
		ft::list<int>(), std::list<int>(), __FUNCTION__, __LINE__);
	test_container_range_constructor(
		ft::list<int>(), std::list<int>(), std::rand, __FUNCTION__, __LINE__);
	test_container_copy_constructor(ft::list<int>(5), __FUNCTION__, __LINE__);
	test_container_assignment_operator(
		ft::list<std::string>(5), __FUNCTION__, __LINE__);
	test_container_assign_count(
		ft::list<int>(), std::list<int>(), 4, __FUNCTION__, __LINE__);
	test_container_assign_range(ft::list<float>(10, 100.0f),
		std::list<float>(10, 100.0f), __FUNCTION__, __LINE__);
	test_container_get_allocator(
		ft::list<char>(), std::list<char>(), __FUNCTION__, __LINE__);
	test_container_begin(
		ft::list<double>(), std::list<double>(), __FUNCTION__, __LINE__);
	test_container_end(ft::list<std::string>(), std::list<std::string>(),
		__FUNCTION__, __LINE__);
	test_container_rbegin(
		ft::list<int>(), std::list<int>(), __FUNCTION__, __LINE__);
	test_container_rend(
		ft::list<char>(), std::list<char>(), __FUNCTION__, __LINE__);
	test_container_empty(
		ft::list<int>(), std::list<int>(), __FUNCTION__, __LINE__);
	test_container_not_empty(
		ft::list<int>(1, 1), std::list<int>(1, 1), __FUNCTION__, __LINE__);
	test_container_max_size(
		ft::list<int>(), std::list<int>(), __FUNCTION__, __LINE__);
	test_container_resize(ft::list<char>(1, 'a'), std::list<char>(1, 'a'),
		__FUNCTION__, __LINE__);
	test_container_front(
		ft::list<int>(), std::list<int>(), 123, __FUNCTION__, __LINE__);
	test_container_back(
		ft::list<int>(), std::list<int>(), 123, __FUNCTION__, __LINE__);
	test_container_push_front(
		ft::list<int>(), std::list<int>(), 123, __FUNCTION__, __LINE__);
	test_container_pop_front(
		ft::list<int>(), std::list<int>(), __FUNCTION__, __LINE__);
	test_container_push_back(
		ft::list<int>(), std::list<int>(), 123, __FUNCTION__, __LINE__);
	test_container_pop_back(
		ft::list<int>(), std::list<int>(), __FUNCTION__, __LINE__);
	test_container_insert_one(
		ft::list<int>(), std::list<int>(), 1, __FUNCTION__, __LINE__);
	test_container_insert_count(
		ft::list<int>(), std::list<int>(), 42, __FUNCTION__, __LINE__);
	test_container_insert_range(
		ft::list<int>(), std::list<int>(), __FUNCTION__, __LINE__);
	test_container_erase_position(
		ft::list<int>(), std::list<int>(), std::rand, __FUNCTION__, __LINE__);
	test_container_erase_range(
		ft::list<int>(), std::list<int>(), std::rand, __FUNCTION__, __LINE__);
	test_container_swap(
		ft::list<int>(), std::list<int>(), __FUNCTION__, __LINE__);
	test_container_clear(
		ft::list<int>(), std::list<int>(), __FUNCTION__, __LINE__);
	test_list_splice_entire_list(
		ft::list<int>(), std::list<int>(), std::rand, __FUNCTION__, __LINE__);
	test_list_splice_one_iterator(
		ft::list<int>(), std::list<int>(), std::rand, __FUNCTION__, __LINE__);
	test_list_splice_range(
		ft::list<int>(), std::list<int>(), std::rand, __FUNCTION__, __LINE__);
	test_list_remove(
		ft::list<int>(), std::list<int>(), std::rand, __FUNCTION__, __LINE__);
	test_list_remove_if(ft::list<int>(), std::list<int>(), std::rand, is_even,
		__FUNCTION__, __LINE__);
	test_list_unique(
		ft::list<int>(), std::list<int>(), std::rand, __FUNCTION__, __LINE__);
	test_list_unique_predicate(ft::list<int>(), std::list<int>(), std::rand,
		both_numbers_are_even, __FUNCTION__, __LINE__);
	test_list_merge(
		ft::list<int>(), std::list<int>(), std::rand, __FUNCTION__, __LINE__);
	test_list_merge_compare(ft::list<int>(), std::list<int>(), std::rand,
		ft::less<int>(), __FUNCTION__, __LINE__);
	test_container_sort(
		ft::list<int>(), std::list<int>(), std::rand, __FUNCTION__, __LINE__);
	test_container_sort_compare(ft::list<int>(), std::list<int>(), std::rand,
		ft::less<int>(), __FUNCTION__, __LINE__);
	test_list_reverse(
		ft::list<int>(), std::list<int>(), std::rand, __FUNCTION__, __LINE__);
	test_container_equal_operator(
		ft::list<int>(), std::list<int>(), 123, __FUNCTION__, __LINE__);
	test_container_notequal_operator(
		ft::list<int>(), std::list<int>(), 123, __FUNCTION__, __LINE__);
	test_container_less_operator(ft::list<std::string>(),
		std::list<std::string>(), std::string("abcd"), std::string("bcde"),
		__FUNCTION__, __LINE__);
	test_container_greater_operator(ft::list<std::string>(),
		std::list<std::string>(), std::string("abcd"), std::string("bcde"),
		__FUNCTION__, __LINE__);
	test_container_lessequal_operator(ft::list<std::string>(),
		std::list<std::string>(), std::string("abcd"), std::string("bcde"),
		__FUNCTION__, __LINE__);
	test_container_greaterequal_operator(ft::list<std::string>(),
		std::list<std::string>(), std::string("abcd"), std::string("bcde"),
		__FUNCTION__, __LINE__);
	test_container_swap_overload(
		ft::list<int>(), std::list<int>(), __FUNCTION__, __LINE__);
}

void test_queue() {
	test_container_adaptor_default_constructor(
		ft::queue<int>(), std::queue<int>(), __FUNCTION__, __LINE__);
	test_container_adaptor_empty(
		ft::queue<int>(), std::queue<int>(), std::rand, __FUNCTION__, __LINE__);
	test_container_adaptor_size(
		ft::queue<int>(), std::queue<int>(), std::rand, __FUNCTION__, __LINE__);
	test_container_adaptor_front(
		ft::queue<int>(), std::queue<int>(), std::rand, __FUNCTION__, __LINE__);
	test_container_adaptor_back(
		ft::queue<int>(), std::queue<int>(), std::rand, __FUNCTION__, __LINE__);
	test_queue_push(
		ft::queue<int>(), std::queue<int>(), std::rand, __FUNCTION__, __LINE__);
	test_queue_pop(
		ft::queue<int>(), std::queue<int>(), std::rand, __FUNCTION__, __LINE__);
	test_container_adaptor_comparison_operators(
		ft::queue<int>(), std::rand, __FUNCTION__, __LINE__);
}

void test_stack() {
	test_container_adaptor_default_constructor(
		ft::stack<int>(), std::stack<int>(), __FUNCTION__, __LINE__);
	test_container_adaptor_empty(
		ft::stack<int>(), std::stack<int>(), std::rand, __FUNCTION__, __LINE__);
	test_container_adaptor_size(
		ft::stack<int>(), std::stack<int>(), std::rand, __FUNCTION__, __LINE__);
	test_container_adaptor_top(
		ft::stack<int>(), std::stack<int>(), std::rand, __FUNCTION__, __LINE__);
	test_stack_push(
		ft::stack<int>(), std::stack<int>(), std::rand, __FUNCTION__, __LINE__);
	test_stack_pop(
		ft::stack<int>(), std::stack<int>(), std::rand, __FUNCTION__, __LINE__);
	test_container_adaptor_comparison_operators(
		ft::stack<int>(), std::rand, __FUNCTION__, __LINE__);
}

void test_map() {
	test_map_default_constructor(
		ft::map<int, int>(), std::map<int, int>(), __FUNCTION__, __LINE__);
	test_map_range_constructor(ft::map<int, std::string>(),
		ft::pair<int, std::string>(), std::map<int, std::string>(),
		std::pair<int, std::string>(), std::rand, generateRandomString,
		__FUNCTION__, __LINE__);
	test_map_copy_constructor(ft::map<int, std::string>(),
		ft::pair<int, std::string>(), std::map<int, std::string>(),
		std::pair<int, std::string>(), std::rand, generateRandomString,
		__FUNCTION__, __LINE__);
	test_map_assignment_operator(ft::map<int, std::string>(),
		ft::pair<int, std::string>(), std::map<int, std::string>(),
		std::pair<int, std::string>(), std::rand, generateRandomString,
		__FUNCTION__, __LINE__);
	test_map_begin(ft::map<int, std::string>(), ft::pair<int, std::string>(),
		std::map<int, std::string>(), std::pair<int, std::string>(), std::rand,
		generateRandomString, __FUNCTION__, __LINE__);
	test_map_end(ft::map<int, std::string>(), ft::pair<int, std::string>(),
		std::map<int, std::string>(), std::pair<int, std::string>(), std::rand,
		generateRandomString, __FUNCTION__, __LINE__);
	test_map_rbegin(ft::map<int, std::string>(), ft::pair<int, std::string>(),
		std::map<int, std::string>(), std::pair<int, std::string>(), std::rand,
		generateRandomString, __FUNCTION__, __LINE__);
	test_map_rend(ft::map<int, std::string>(), ft::pair<int, std::string>(),
		std::map<int, std::string>(), std::pair<int, std::string>(), std::rand,
		generateRandomString, __FUNCTION__, __LINE__);
	test_map_empty(ft::map<int, std::string>(), ft::pair<int, std::string>(),
		std::map<int, std::string>(), std::pair<int, std::string>(), std::rand,
		generateRandomString, __FUNCTION__, __LINE__);
	test_map_element_access(ft::map<int, std::string>(),
		ft::pair<int, std::string>(), std::map<int, std::string>(),
		std::pair<int, std::string>(), std::rand, generateRandomString,
		__FUNCTION__, __LINE__);
}

int main() {
	std::srand(std::time(NULL));
	test_vector();
	test_list();
	test_queue();
	test_stack();
	test_map();
	if (g_errors) {
		std::cout << g_errors << " errors\n";
	} else {
		std::cout << "All tests passed!\n";
	}
	return g_errors ? 1 : 0;
}
