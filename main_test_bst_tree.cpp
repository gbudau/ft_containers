#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "bst_tree.hpp"
#include "utility.hpp"
#include "utils.hpp"

template <class BstTree>
void print_bst_content(const BstTree &bst) {
	typename BstTree::const_iterator it = bst.begin();
	typename BstTree::const_iterator ite = bst.end();
	while (it != ite) {
		std::cout << (*it++).second << '|';
	}
	std::cout << '\n';
}

template <class BstTree>
void reverse_print_bst_content(const BstTree &bst) {
	typename BstTree::const_reverse_iterator it = bst.rbegin();
	typename BstTree::const_reverse_iterator ite = bst.rend();
	while (it != ite) {
		std::cout << (*it++).second << '|';
	}
	std::cout << '\n';
}

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
	print_bst_content(bst_range);
	reverse_print_bst_content(bst_range);

	ft::pair<custom_bst_tree::iterator, bool> ret;
	ret = bst_range.insert(ft::make_pair(100, "one hundred"));
	std::cout << "\nReturn of insert with duplicate key (100): "
			  << std::boolalpha << ret.second << ", key: " << (*ret.first).first
			  << '\n';
	ret = bst_range.insert(ft::make_pair(500, "five hundred"));
	std::cout << "Return of insert with new key (500): " << std::boolalpha
			  << ret.second << ", key: " << (*ret.first).first << '\n';

	custom_bst_tree bst_copy_construct(bst_range.begin(), bst_range.end());

	bst_copy_construct.erase(bst_copy_construct.begin());
	print_bst_content(bst_copy_construct);

	bst.swap(bst_copy_construct);
	print_bst_content(bst_copy_construct);

	bst_copy_construct = bst;
	std::cout << "\nContent of containers after assignment operator:\n";
	print_bst_content(bst_copy_construct);
	print_bst_content(bst);

	custom_bst_tree::key_compare compare = bst.key_comp();
	std::cout << compare(1, 2) << '\n';

	std::cout << "\nFind key 100:\n";
	custom_bst_tree::iterator it = bst.find(100);
	if (it != bst.end()) {
		std::cout << "key: " << (*it).first << ", value: " << (*it).second
				  << '\n';
	} else {
		std::cout << "Key not found\n";
	}

	std::cout << "\nFind key 200:\n";
	custom_bst_tree::const_iterator cit = bst.find(200);
	if (cit != bst.end()) {
		std::cout << "key: " << (*cit).first << ", value: " << (*cit).second
				  << '\n';
	} else {
		std::cout << "Key not found\n";
	}

	std::cout << "\nRemoving 200 from bst\n";
	std::size_t n = bst.erase(200);
	std::cout << "Number of elements removed: " << n << '\n';
	print_bst_content(bst);

	std::cout << "\nRemoving 200 from bst\n";
	n = bst.erase(200);
	std::cout << "Number of elements removed: " << n << '\n';
	print_bst_content(bst);

	std::cout << "\nNumber of elements with 100 as key: " << bst.count(100)
			  << '\n';
	std::cout << "Number of elements with 300 as key: " << bst.count(300)
			  << '\n';

	it = bst.lower_bound(400);
	std::cout << "bst key with lower bound than 400: ";
	if (it != bst.end()) {
		std::cout << (*it).first << '\n';
	} else {
		std::cout << "None\n";
	}

	it = bst.upper_bound(400);
	std::cout << "bst key with upper bound than 400: ";
	if (it != bst.end()) {
		std::cout << (*it).first << '\n';
	} else {
		std::cout << "None\n";
	}

	ft::pair<custom_bst_tree::iterator, custom_bst_tree::iterator> pair_it;
	pair_it = bst.equal_range(400);

	std::cout << "\nTesting equal_range:\n";
	std::cout << "bst key with lower bound than 400: ";
	if (pair_it.first != bst.end()) {
		std::cout << (*pair_it.first).first << '\n';
	} else {
		std::cout << "None\n";
	}

	std::cout << "bst key with upper bound than 400: ";
	if (pair_it.second != bst.end()) {
		std::cout << (*pair_it.second).first << '\n';
	} else {
		std::cout << "None\n";
	}
}
