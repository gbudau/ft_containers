#include <iostream>
#include "vector.hpp"

int	main() {
	ft::vector<int> v;

	(void)v;
	ft::vector<int> v2(3, 42);

	std::cout << v.size() << "\n";
	std::cout << v2.size() << "\n";
}
