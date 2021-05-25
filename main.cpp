#include <iostream>
#include <vector>
#include <cassert>
#include <list>
#include "vector.hpp"

int	main() {
	std::vector<int> v;
	ft::vector<int> v1;
	const int N = 5;

	(void)v;
	ft::vector<int> v2(3, 42);

	std::cout << "v1 Size: " << v1.size() << "\n";
	std::cout << "v2 Size: " << v2.size() << "\n";
	std::cout << "v2 Capacity: " << v2.capacity() << "\n";
	std::cout << "v1 Max Size: " << v1.max_size() << "\n";
	std::cout << "v Max Size: " << v.max_size() << "\n";
	std::cout << "v1 empty()?: " << v1.empty() << "\n";
	std::cout << "v2 empty()?: " << v2.empty() << "\n";

	std::cout << "Testing allocator with " << N << " values\n";
	int *p = v1.get_allocator().allocate(N);
	for (int i = 0; i < N; i++) {
		v1.get_allocator().construct(p + i, i);
		std::cout << p[i] << "\n";
		v1.get_allocator().destroy(p + i);
	}
	v1.get_allocator().deallocate(p, N);
	v2.erase(v2.begin());
	v2.erase(v2.begin());
	std::cout << "v2 Size: " << v2.size() << "\n";
	ft::vector<int> v3(5, 42);
	std::cout << "v3 Size: " << v3.size() << "\n";
	v3.erase(v3.begin(), v3.end());
	std::cout << "v3 Size after erase(begin(), end()): " << v3.size() << "\n";
	v3.insert(v3.begin(), 123);
	std::cout << "v3 Size after insert(): " << v3.size() << "\n";

	ft::vector<int> v4;
	std::cout << "v4 after default construct, size: " << v4.size() << " ,capacity: " << v4.capacity() << "\n";
	v4.insert(v4.begin(), 1);
	std::cout << "v4 after insert, size: " << v4.size() << " ,capacity: " << v4.capacity() << "\n";
	v4.insert(v4.end(), 2);
	std::cout << "v4 after insert, size: " << v4.size() << " ,capacity: " << v4.capacity() << "\n";
	v4.insert(v4.begin(), 3);
	std::cout << "v4 after insert, size: " << v4.size() << " ,capacity: " << v4.capacity() << "\n";
	v4.insert(v4.begin(), 4);
	std::cout << "v4 after insert, size: " << v4.size() << " ,capacity: " << v4.capacity() << "\n";

	std::vector<int> v5;
	std::cout << "v5 after default construct, size: " << v5.size() << " ,capacity: " << v5.capacity() << "\n";
	v5.insert(v5.begin(), 1);
	std::cout << "v5 after insert, size: " << v5.size() << " ,capacity: " << v5.capacity() << "\n";
	v5.insert(v5.end(), 2);
	std::cout << "v5 after insert, size: " << v5.size() << " ,capacity: " << v5.capacity() << "\n";
	v5.insert(v5.begin(), 3);
	std::cout << "v5 after insert, size: " << v5.size() << " ,capacity: " << v5.capacity() << "\n";
	v5.insert(v5.begin(), 4);
	std::cout << "v5 after insert, size: " << v5.size() << " ,capacity: " << v5.capacity() << "\n";

	ft::vector<int> v6(5, 42);
	std::cout << "v6 size: " << v6.size() << ", capacity: " << v6.capacity() << "\n";
	v6.insert(v6.end(), 1);
	std::cout << "v6 size: " << v6.size() << ", capacity: " << v6.capacity() << "\n";
	v6.insert(v6.begin(), 1);
	std::cout << "v6 size: " << v6.size() << ", capacity: " << v6.capacity() << "\n";
	for (ft::vector<int>::iterator it = v6.begin(); it != v6.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << "\n";

	std::list<int>	l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	ft::vector<int>	v7(l.begin(), l.end());
	for (ft::vector<int>::iterator it = v7.begin(); it != v7.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << "\n";

	return 0;
}
