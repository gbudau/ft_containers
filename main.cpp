#include <iostream>
#include <vector>
#include "vector.hpp"

int	main() {
	std::vector<int> v;
	ft::vector<int> v1;

	(void)v;
	ft::vector<int> v2(3, 42);

	std::cout << v1.size() << "\n";
	std::cout << v2.size() << "\n";
	std::cout << v1.max_size() << "\n";
	std::cout << v.max_size() << "\n";
}
