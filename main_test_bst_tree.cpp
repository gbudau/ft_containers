#include <iostream>
#include <memory>
#include <string>
#include "bst_tree.hpp"
#include "utility.hpp"
#include "utils.hpp"

int main() {
	ft::bst_tree<int, ft::pair<int, std::string>,
		ft::select_first<int, std::string>, ft::less<int>,
		std::allocator<ft::pair<int, std::string> > >
		bst;
	std::cout << bst.size() << '\n';
	std::cout << std::boolalpha << bst.empty() << '\n';
	std::cout << bst.max_size() << '\n';
}
