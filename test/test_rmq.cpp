#include <iostream>
#include <random>
#include <vector>
#include <cassert>

#include "../src/rmq.hpp"
#include "../brute/rmq_brute.hpp"

void test_rmq(int min_n, int max_n, int seed = 2137) {
	std::cerr << "TEST(rmq, " << min_n << ", " << max_n << ", " << seed << ")\n";

	std::mt19937 rng(seed);

	auto randint = [&](int a, int b) {
		return std::uniform_int_distribution<int>(a, b)(rng);
	};

	for (int test = 0; test < 10000; test++) {
		int n = randint(min_n, max_n);
		std::vector<int> s(n);

		for (int &c : s) {
			c = randint(0, n - 1);
		}

		RangeMinimumQuery<int> fast(s);
		RangeMinimumQueryBrute<int> slow(s);

		int q = randint(min_n, max_n);

		while (q--) {
			int l = randint(0, n - 1);
			int r = randint(l + 1, n);

			if(fast.query(l, r) != slow.query(l, r)) {
				std::cerr << "v: ";
				for (int x : s) {
					std::cerr << x << ' ';
				}
				std::cerr << '\n';

				std::cerr << "l, r: " << l << ' ' << r << '\n';

				std::cerr << fast.query(l, r) << " vs " << slow.query(l, r) << '\n';

				assert(false);
			}
		}
	}
}


int main() {

	test_rmq(1, 5, 1);
	test_rmq(1, 25, 1);
	test_rmq(1, 100, 1);
	test_rmq(1, 500, 1);

	return 0;
}