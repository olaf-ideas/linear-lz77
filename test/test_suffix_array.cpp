#include <iostream>
#include <random>
#include <vector>
#include <cassert>

#include "../suffix_array.hpp"
#include "../brute/suffix_array_brute.hpp"

void test_suffix_array(int min_n, int max_n, int seed = 2137) {
	std::cerr << "TEST(suffix_array, " << min_n << ", " << max_n << ", " << seed << ")\n";

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

		auto fast = suffix_array(s);
		auto slow = suffix_array_brute(s);

		if (fast != slow) {
			std::cerr << "w: ";
			for (int c : s)
				std::cerr << c << ' ';
			std::cerr << '\n';

			std::cerr << "A: ";
			for (int i : fast)
				std::cerr << i << ' ';
			std::cerr << '\n';
			
			std::cerr << "B: ";
			for (int i : slow)
				std::cerr << i << ' ';
			std::cerr << '\n';

			assert(false);
		}
	}
}

void test_suffix_array_binary(int min_n, int max_n, int seed = 2137) {
	std::cerr << "TEST(suffix_array, " << min_n << ", " << max_n << ", " << seed << ")\n";
	
	std::mt19937 rng(seed);

	auto randint = [&](int a, int b) {
		return std::uniform_int_distribution<int>(a, b)(rng);
	};

	for (int test = 0; test < 1000; test++) {
		int n = randint(min_n, max_n);
		std::vector<int> s(n);

		int zero = randint(0, n - 1);
		int one = randint(0, n - 1);

		for (int &c : s) {
			c = (randint(0, 1) == 0 ? zero : one);
		}

		assert(suffix_array_brute(s) == suffix_array(s));
	}
}

int main() {

  test_suffix_array(1, 10, 1);
  test_suffix_array(1, 100, 2);
  test_suffix_array(1, 200, 3);

  test_suffix_array_binary(1, 5, 4);
  test_suffix_array_binary(1, 100, 5);
  test_suffix_array_binary(1, 200, 6);

  return 0;
}