#include <iostream>
#include <memory>
#include <string>
#include "bst_tree.hpp"
#include "utility.hpp"
#include "utils.hpp"

int main() {
	typedef ft::pair<int, std::string> value_type;
	typedef int                        key_type;
	ft::bst_tree<key_type, value_type, ft::select_first<value_type, key_type>,
		ft::less<int>, std::allocator<value_type> >
		bst;
	std::cout << bst.size() << '\n';
	std::cout << std::boolalpha << bst.empty() << '\n';
	std::cout << bst.max_size() << '\n';
	bst.insert(ft::make_pair(1, "one"));
	std::cout << bst.size() << '\n';
	bst.insert(ft::make_pair(2, "two"));
	std::cout << bst.size() << '\n';
	bst.insert(ft::make_pair(3, "three"));
	std::cout << bst.size() << '\n';
	bst.insert(ft::make_pair(3, "three"));
	std::cout << bst.size() << '\n';
}
