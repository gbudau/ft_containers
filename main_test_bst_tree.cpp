#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "bst_tree.hpp"
#include "utility.hpp"
#include "utils.hpp"

int main() {
	typedef ft::pair<int, std::string> value_type;
	typedef int                        key_type;
	typedef ft::bst_tree<key_type, value_type,
		ft::select_first<value_type, key_type>, ft::less<int>,
		std::allocator<value_type> >
							   custom_bst_tree;

	custom_bst_tree            bst;
	std::map<int, std::string> m;
	std::cout << bst.size() << '\n';
	std::cout << std::boolalpha << bst.empty() << '\n';
	std::cout << bst.max_size() << '\n';
	std::cout << m.max_size() << '\n';
	bst.insert(ft::make_pair(1, "one"));
	std::cout << bst.size() << '\n';
	bst.insert(ft::make_pair(2, "two"));
	std::cout << bst.size() << '\n';
	bst.insert(ft::make_pair(3, "three"));
	std::cout << bst.size() << '\n';
	bst.insert(ft::make_pair(3, "three"));
	std::cout << bst.size() << '\n';

	std::vector<value_type> v;
	v.push_back(ft::make_pair(100, "one hundred"));
	v.push_back(ft::make_pair(200, "two hundred"));
	v.push_back(ft::make_pair(300, "three hundred"));
	v.push_back(ft::make_pair(400, "four hundred"));
	v.push_back(ft::make_pair(400, "four hundred"));
	custom_bst_tree bst_range(v.begin(), v.end());
	std::cout << bst_range.size() << '\n';
	custom_bst_tree::iterator it = bst_range.begin();
	while (it != bst_range.end()) {
		std::cout << (*it++).second << '|';
	}
	std::cout << '\n';
	custom_bst_tree::reverse_iterator rit = bst_range.rbegin();
	while (rit != bst_range.rend()) {
		std::cout << (*rit++).second << '|';
	}
	std::cout << '\n';
	ft::pair<custom_bst_tree::iterator, bool> ret;
	ret = bst_range.insert(ft::make_pair(100, "one hundred"));
	std::cout << "Return of insert with duplicate key (100): " << std::boolalpha
			  << ret.second << ", key: " << (*ret.first).first << '\n';
	ret = bst_range.insert(ft::make_pair(500, "five hundred"));
	std::cout << "Return of insert with new key (500): " << std::boolalpha
			  << ret.second << ", key: " << (*ret.first).first << '\n';
	custom_bst_tree bst_copy_construct(bst_range.begin(), bst_range.end());
	bst_copy_construct.erase(bst_copy_construct.begin());
	it = bst_copy_construct.begin();
	while (it != bst_copy_construct.end()) {
		std::cout << (*it++).second << '|';
	}
	std::cout << '\n';
}
