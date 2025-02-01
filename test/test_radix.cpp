#include <iostream>
#include <vector>
#include <array>
#include <cassert>
#include <random>

#include "../src/radix.hpp"
#include "../brute/radix_brute.hpp"

template <std::size_t max_size>
void test_radix_sort_order(int min_n, int max_n, int seed = 2137) {
	std::cerr << "TEST(radix_sort_order<" << max_size << ">, " << min_n << ", " << max_n << ", " << seed << ")\n";

	std::mt19937 rng(seed);
	
	auto randint = [&](int a, int b) {
		return std::uniform_int_distribution<int>(a, b)(rng);
	};
	
	for (int test = 0; test < 1000; test++) {
		int n = randint(min_n, max_n);
		
		std::vector<std::array<int, max_size>> v(n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < (int) max_size; j++)
				v[i][j] = randint(0, n - 1);

		assert(radix_sort_order(n, v) == radix_sort_order_brute(n, v));
	}

	if constexpr (max_size > 1) {
		test_radix_sort_order<max_size - 1>(min_n, max_n, seed);
	}
}

int main() {

	test_radix_sort_order<10>(1, 10, 1);

  return 0;
}