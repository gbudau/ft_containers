#include <cassert>
#include <string>
#include <vector>
#include "vector.hpp"

template <class Container1, class Container2>
static void assert_equal_size_and_capacity(
	const Container1 &c1, const Container2 &c2) {

	assert(c1.size() == c2.size());
	assert(c1.capacity() == c2.capacity());
}

template <class Container1, class Container2>
static void assert_equal_content(const Container1 &c1, const Container2 &c2) {
	typename Container1::const_iterator it1 = c1.begin();
	typename Container2::const_iterator it2 = c2.begin();

	while (it1 != c1.end() && it2 != c2.end()) {
		assert(*it1++ == *it2++);
	}
	assert(it1 == c1.end() && it2 == c2.end());
}

template <class Container1, class Container2>
static void assert_equal_container(const Container1 &c1, const Container2 &c2) {
	assert_equal_size_and_capacity(c1, c2);
	assert_equal_content(c1, c2);
}

template <class Container1, class Container2>
static void test_container_default_constructor(
	const Container1 &, const Container2 &) {
	Container1 c1;
	Container2 c2;

	assert_equal_size_and_capacity(c1, c2);
}

template <class Container1, class Container2>
static void test_container_count_constructor(
	const Container1 &c1, const Container2 &c2) {
	assert_equal_size_and_capacity(c1, c2);
}

template <class Container1, class Container2>
static void test_container_range_constructor(
	const Container1 &c1, const Container2 &c2) {
	Container1 c;

	for (typename Container1::const_iterator it = c1.begin(); it != c1.end();
		 it++) {
		c.push_back(*it);
	}
	for (typename Container2::const_iterator it = c2.begin(); it != c2.end();
		 it++) {
		c.push_back(*it);
	}

	Container1 c_a(c.begin(), c.end());
	Container2 c_b(c.begin(), c.end());
	assert_equal_container(c_a, c_b);
}

template <class Container1>
static void test_container_copy_constructor(const Container1 &c1) {
	Container1 c2(c1);

	assert_equal_container(c1, c2);
}

template <class Container1>
static void test_container_assignment_operator(const Container1 &c1) {
	Container1 c2 = c1;

	assert_equal_container(c1, c2);
}

template <class Container1, class Container2, typename T>
static void test_container_assign_count(
	const Container1 &, const Container2 &, const T &v) {
	Container1 c1;
	Container2 c2;

	c1.assign(10, v);
	c2.assign(10, v);
	assert_equal_container(c1, c2);
}

template <class Container1, class Container2>
static void test_container_assign_range(
	const Container1 &c1, const Container2 &c2) {
	Container1 c_a;
	Container2 c_b;
	c_a.assign(c1.begin(), c1.end());
	c_b.assign(c2.begin(), c2.end());
	assert_equal_container(c_a, c_b);
}

template <class Container1, class Container2>
static void test_container_get_allocator(
	const Container1 &c1, const Container2 &c2) {
	assert(c1.get_allocator() == c2.get_allocator());
}

template <class Container1, class Container2>
static void test_container_begin(const Container1 &, const Container2 &) {
	Container1 c1(5);
	Container2 c2(5);

	assert_equal_container(c1, c2);
	typename Container1::iterator it1 = c1.begin();
	typename Container2::iterator it2 = c2.begin();
	assert(*it1 == *it2);

	typename Container1::const_iterator it1c = c1.begin();
	typename Container2::const_iterator it2c = c2.begin();
	assert(*it1c == *it2c);
}

template <class Container1, class Container2>
static void test_container_end(const Container1 &, const Container2 &) {
	Container1 c1(1);
	Container2 c2(1);

	assert(c1.size() && c2.size());
	assert_equal_container(c1, c2);
	typename Container1::iterator it1 = c1.end();
	typename Container2::iterator it2 = c2.end();
	// This works only for the containers that have bidirectional_iterator+
	assert(*(--it1) == *(--it2));

	typename Container1::const_iterator it1c = c1.end();
	typename Container2::const_iterator it2c = c2.end();
	// This works only for the containers that have bidirectional_iterator+
	assert(*(--it1c) == *(--it2c));
}

template <class Container1, class Container2>
static void test_container_rbegin(const Container1 &, const Container2 &) {
	Container1 c1(5);
	Container2 c2(5);

	assert_equal_container(c1, c2);
	typename Container1::reverse_iterator rit1 = c1.rbegin();
	typename Container2::reverse_iterator rit2 = c2.rbegin();
	assert(*rit1 == *rit2);

	typename Container1::const_reverse_iterator rit1c = c1.rbegin();
	typename Container2::const_reverse_iterator rit2c = c2.rbegin();
	assert(*rit1c == *rit2c);
}

template <class Container1, class Container2>
static void test_container_rend(const Container1 &, const Container2 &) {
	Container1 c1(1);
	Container2 c2(1);

	assert(c1.size() && c2.size());
	assert_equal_container(c1, c2);
	typename Container1::reverse_iterator rit1 = c1.rend();
	typename Container2::reverse_iterator rit2 = c2.rend();
	// This works only for the containers that have bidirectional_iterator+
	assert(*(--rit1) == *(--rit2));

	typename Container1::const_reverse_iterator rit1c = c1.rend();
	typename Container2::const_reverse_iterator rit2c = c2.rend();
	// This works only for the containers that have bidirectional_iterator+
	assert(*(--rit1c) == *(--rit2c));
}

template <class Container1, class Container2>
static void test_container_max_size(
	const Container1 &c1, const Container2 &c2) {
	assert(c1.max_size() == c2.max_size());
}

template <class Container1, class Container2>
static void test_container_resize(const Container1 &c1, const Container2 &c2) {
	Container1 c_a(c1);
	Container2 c_b(c2);

	assert_equal_container(c_b, c_a);
	c_a.resize(5);
	c_b.resize(5);
	assert_equal_container(c_b, c_a);
	c_a.resize(2);
	c_b.resize(2);
	assert_equal_container(c_b, c_a);
	c_a.resize(12);
	c_b.resize(12);
	assert_equal_container(c_b, c_a);
}

template <class Container1, class Container2>
static void test_container_empty(const Container1 &c1, const Container2 &c2) {
	assert(c1.empty() == c2.empty());
}

template <class Container1, class Container2>
static void test_container_not_empty(
	const Container1 &c1, const Container2 &c2) {
	assert(c1.empty() == c2.empty());
}

template <class T, class Container1, class Container2>
static void test_container_array_subscript(
	const Container1 &, const Container2 &, const T &val) {
	Container1 c1(5);
	Container2 c2(5);

	assert_equal_container(c1, c2);
	for (std::size_t i = 0; i < c1.size() && i < c2.size(); i++) {
		c1.at(i) = val;
		c2.at(i) = val;
	}
	assert_equal_container(c1, c2);

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
	assert(a == b);
}

template <class T, class Container1, class Container2>
static void test_container_at(
	const Container1 &, const Container2 &, const T &val) {
	Container1 c1(5);
	Container2 c2(5);

	assert_equal_container(c1, c2);
	for (std::size_t i = 0; i < c1.size() && i < c2.size(); i++) {
		c1[i] = val;
		c2[i] = val;
	}
	assert_equal_container(c1, c2);
}

template <class T, class Container1, class Container2>
static void test_container_front(
	const Container1 &, const Container2 &, const T &val) {
	Container1 c1(1);
	Container2 c2(1);

	assert_equal_container(c1, c2);
	typename Container1::iterator it1 = c1.begin();
	typename Container2::iterator it2 = c2.begin();
	for (; it1 != c1.end() && it2 != c2.end(); it1++, it2++) {
		*it1 = val;
		*it2 = val;
	}
	assert_equal_container(c1, c2);
	assert(c1.front() == c2.front());
}

template <class T, class Container1, class Container2>
static void test_container_back(
	const Container1 &, const Container2 &, const T &val) {
	Container1 c1(1);
	Container2 c2(1);

	assert_equal_container(c1, c2);
	typename Container1::iterator it1 = c1.begin();
	typename Container2::iterator it2 = c2.begin();
	for (; it1 != c1.end() && it2 != c2.end(); it1++, it2++) {
		*it1 = val;
		*it2 = val;
	}
	assert_equal_container(c1, c2);
	assert(c1.back() == c2.back());
}

template <class Container1, class Container2>
static void test_container_reserve(const Container1 &c1, const Container2 &c2) {
	Container1 c_a(c1);
	Container2 c_b(c2);

	assert_equal_container(c_b, c_a);
	c_a.reserve(0);
	c_b.reserve(0);
	assert_equal_container(c_b, c_a);
	c_a.reserve(c_a.size());
	c_b.reserve(c_b.size());
	assert_equal_container(c_b, c_a);
	c_a.reserve(c_a.size() * 2);
	c_b.reserve(c_b.size() * 2);
	assert_equal_container(c_b, c_a);
}

template <class T, class Container1, class Container2>
static void test_container_push_back(
	const Container1 &, const Container2 &, const T &val) {
	Container1 c1;
	Container2 c2;

	assert_equal_container(c1, c2);
	for (int i = 0; i < 10; i++) {
		c1.push_back(val);
		c2.push_back(val);
		assert_equal_container(c1, c2);
	}
	assert_equal_container(c1, c2);
}

template <class Container1, class Container2>
static void test_container_pop_back(const Container1 &, const Container2 &) {
	Container1 c1(10);
	Container2 c2(10);

	assert_equal_container(c1, c2);
	for (std::size_t i = 0; i < c1.size() && i < c2.size(); i++) {
		c1.pop_back();
		c2.pop_back();
		assert_equal_container(c1, c2);
	}
	assert_equal_container(c1, c2);
}

template <class T, class Container1, class Container2>
static void test_container_insert_one(
	const Container1 &, const Container2 &, const T &val) {
	Container1 c1;
	Container2 c2;

	assert_equal_container(c1, c2);
	typename Container1::iterator it1 = c1.insert(c1.end(), val);
	typename Container2::iterator it2 = c2.insert(c2.end(), val);
	assert(*it1 == *it2);
	assert_equal_container(c1, c2);
	it1 = c1.insert(c1.begin(), val);
	it2 = c2.insert(c2.begin(), val);
	assert(*it1 == *it2);
	assert_equal_container(c1, c2);
}

template <class T, class Container1, class Container2>
static void test_container_insert_count(
	const Container1 &, const Container2 &, const T &val) {
	Container1 c1;
	Container2 c2;

	assert_equal_container(c1, c2);
	c1.insert(c1.end(), 0, val);
	c2.insert(c2.end(), 0, val);
	assert_equal_container(c1, c2);
	c1.insert(c1.begin(), 1, val);
	c2.insert(c2.begin(), 1, val);
	assert_equal_container(c1, c2);
	c1.insert(c1.begin(), 10, val);
	c2.insert(c2.begin(), 10, val);
	assert_equal_container(c1, c2);
	c1.insert(c1.begin(), 1, val);
	c2.insert(c2.begin(), 1, val);
	assert_equal_container(c1, c2);
	c1.insert(c1.begin(), 5, val);
	c2.insert(c2.begin(), 5, val);
	assert_equal_container(c1, c2);
}

template <class Container1, class Container2>
static void test_container_insert_range(
	const Container1 &, const Container2 &) {
	Container1 c1;
	Container2 c2;
	Container1 t1(10);
	Container2 t2(10);

	c1.insert(c1.begin(), t1.begin(), t1.end());
	c2.insert(c2.begin(), t2.begin(), t2.end());
	assert_equal_container(c1, c2);
	c1.insert(c1.end(), t1.begin(), t1.end());
	c2.insert(c2.end(), t2.begin(), t2.end());
	assert_equal_container(c1, c2);
	typename Container1::iterator it1 = c1.begin();
	typename Container2::iterator it2 = c2.begin();
	for (std::size_t i = 0; i < c1.size() / 2 && i < c2.size() / 2; i++) {
		it1++;
		it2++;
	}
	c1.insert(it1, t1.begin(), t1.end());
	c2.insert(it2, t2.begin(), t2.end());
	assert_equal_container(c1, c2);

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
	assert_equal_container(c1, c2);
}

template <class Container1, class Container2>
static void test_container_erase_position(
	const Container1 &, const Container2 &) {
	Container1                    c1(10);
	Container2                    c2(10);
	typename Container1::iterator c1_it;
	typename Container2::iterator c2_it;

	assert_equal_container(c1, c2);
	for (std::size_t i = 0; i < c1.size(); i++) {
		c1_it = c1.erase(c1.begin());
		c2_it = c2.erase(c2.begin());
		assert(*c1_it == *c2_it);
		assert_equal_container(c1, c2);
	}
	assert_equal_container(c1, c2);
}

template <class Container1, class Container2>
static void test_container_erase_range(const Container1 &, const Container2 &) {
	Container1 c1;
	Container2 c2;

	assert_equal_container(c1, c2);
	typename Container1::iterator c1_it = c1.erase(c1.begin(), c1.end());
	typename Container2::iterator c2_it = c2.erase(c2.begin(), c2.end());
	assert(c1_it == c1.end() && c2_it == c2.end());
	assert_equal_container(c1, c2);
	c1 = Container1(5);
	c2 = Container2(5);
	c1_it = c1.erase(c1.begin(), c1.end());
	c2_it = c2.erase(c2.begin(), c2.end());
	assert(c1_it == c1.end() && c2_it == c2.end());
	assert_equal_container(c1, c2);
}

template <class Container1, class Container2>
static void test_container_swap(const Container1 &, const Container2 &) {
	Container1 c1_empty;
	Container2 c2_empty;
	Container1 c1(5);
	Container2 c2(5);

	assert_equal_container(c1_empty, c2_empty);
	assert_equal_container(c1, c2);
	c1.swap(c1_empty);
	c2.swap(c2_empty);
	assert_equal_container(c1_empty, c2_empty);
	assert_equal_container(c1, c2);
}

template <class Container1, class Container2>
static void test_container_clear(const Container1 &, const Container2 &) {
	Container1 c1;
	Container2 c2;

	assert_equal_container(c1, c2);
	c1.clear();
	c2.clear();
	assert_equal_container(c1, c2);
	c1 = Container1(5);
	c2 = Container2(5);
	assert_equal_container(c1, c2);
	c1.clear();
	c2.clear();
	assert_equal_container(c1, c2);
}

static void test_vector() {
	test_container_default_constructor(ft::vector<int>(), std::vector<int>());
	test_container_count_constructor(ft::vector<int>(5), std::vector<int>(5));
	test_container_range_constructor(
		ft::vector<int>(1, 1), std::vector<int>(1, 1));
	test_container_copy_constructor(ft::vector<int>(42));
	test_container_assignment_operator(ft::vector<std::string>(1, "hello"));
	test_container_assign_count(ft::vector<int>(), std::vector<int>(), 42);
	test_container_assign_range(
		ft::vector<float>(10, 100.0f), std::vector<float>(10, 100.0f));
	test_container_get_allocator(ft::vector<char>(), std::vector<char>());
	test_container_begin(ft::vector<double>(), std::vector<double>());
	test_container_end(ft::vector<std::string>(), std::vector<std::string>());
	test_container_rbegin(ft::vector<int>(), std::vector<int>());
	test_container_rend(ft::vector<char>(), std::vector<char>());
	test_container_max_size(ft::vector<int>(), std::vector<int>());
	test_container_resize(ft::vector<char>(1, 'a'), std::vector<char>(1, 'a'));
	test_container_empty(ft::vector<int>(), std::vector<int>());
	test_container_not_empty(ft::vector<int>(1, 1), std::vector<int>(1, 1));
	test_container_array_subscript(ft::vector<int>(), std::vector<int>(), 1);
	test_container_at(ft::vector<int>(), std::vector<int>(), 1);
	test_container_front(ft::vector<int>(), std::vector<int>(), 123);
	test_container_back(ft::vector<int>(), std::vector<int>(), 123);
	test_container_reserve(ft::vector<int>(10, 42), std::vector<int>(10, 42));
	test_container_push_back(ft::vector<int>(), std::vector<int>(), 123);
	test_container_pop_back(ft::vector<int>(), std::vector<int>());
	test_container_insert_one(ft::vector<int>(), std::vector<int>(), 1);
	test_container_insert_count(ft::vector<int>(), std::vector<int>(), 42);
	test_container_insert_range(ft::vector<int>(), std::vector<int>());
	test_container_erase_position(ft::vector<int>(), std::vector<int>());
	test_container_erase_range(ft::vector<int>(), std::vector<int>());
	test_container_swap(ft::vector<int>(), std::vector<int>());
	test_container_clear(ft::vector<int>(), std::vector<int>());
}

int main() {
	test_vector();
}
