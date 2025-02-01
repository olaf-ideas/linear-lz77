#include <iostream>
#include <vector>
#include <array>
#include <cassert>
#include <random>

#include "../src/lz77.hpp"
#include "../brute/lz77_brute.hpp"

void test_lz77(int min_n, int max_n, int seed = 2137) {
	std::cerr << "TEST(test_lz77, " << min_n << ", " << max_n << ", " << seed << ")\n";

	std::mt19937 rng(seed);
	
	auto randint = [&](int a, int b) {
		return std::uniform_int_distribution<int>(a, b)(rng);
	}; 

	for (int test = 0; test < 1000; test++) {
	int n = randint(min_n, max_n);
	std::vector<int> w(n);

	for (int& c : w) {
		c = randint(0, n - 1);
	}

	// std::cerr << "w: ";
	// for (int c : w) {
	//   std::cerr << c << ' ';
	// }
	// std::cerr << '\n';

	auto fast = lz77(w);
	auto slow = lz77_brute(w);

	// std::cerr << "w: ";
	// for (int c : w) {
	//   std::cerr << c << ' ';
	// }
	// std::cerr << '\n';

	// std::cerr << "fast: ";
	// for (auto [pos, len, c] : fast) {
	//   std::cerr << "(" << pos << ',' << len << ',' << c << "), ";
	// }
	// std::cerr << '\n';

	// std::cerr << "slow: ";
	// for (auto [pos, len, c] : slow) {
	//   std::cerr << "(" << pos << ',' << len << ',' << c << "), ";
	// }
	// std::cerr << '\n';

	assert(unroll_lz77(fast, (int) w.size()) == unroll_lz77(slow, (int) w.size()));
	assert(fast.size() == slow.size());
	}
}

int main() {

	test_lz77(1, 5, 1);
	test_lz77(1, 50, 2);
	test_lz77(1, 500, 3);
	test_lz77(1, 1000, 4);

	return 0;
}