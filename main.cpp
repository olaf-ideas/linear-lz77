#include <iostream>

#include "suffix_array.hpp"


int main() {

	std::vector<int> w{0, 1, 0, 0, 1};

	std::cerr << "W      : ";
	for (int x : w)
		std::cerr << x << ' ';
	std::cerr << '\n';

	auto sa = suffix_array(w);
	std::cerr << "SA fast: ";
	for (int x : sa)
		std::cerr << x << ' ';
	std::cerr << '\n';
	
	auto sa_brute = suffix_array_brute(w);
	std::cerr << "SA slow: ";
	for (int x : sa_brute)
		std::cerr << x << ' ';
	std::cerr << '\n';

	return 0;
}
