#include <iostream>
#include <vector>
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
}
