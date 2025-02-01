#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <array>
#include <algorithm>
#include <cassert>
#include <random>

std::vector<int> suffix_array_brute(std::vector<int> w) {
	std::vector<int> sa(w.size());
	w.push_back(-1);

	std::iota(sa.begin(), sa.end(), 0);
	std::sort(sa.begin(), sa.end(),
		[&](int i, int j) {
			while (w[i] == w[j]) {
				i++, j++;
			}

			return w[i] < w[j];
		}
	);

	return sa;
}

template <std::size_t size>
std::vector<int> brute_sort_order(int, const std::vector<std::array<int, size>> &v) {
	std::vector<int> order(v.size());
	std::iota(order.begin(), order.end(), 0);
	std::sort(order.begin(), order.end(),
		[&](int i, int j) {
			return v[i] < v[j];
		}
	);

	return order;
}

template <std::size_t size>
std::vector<int> radix_sort_order(int m, const std::vector<std::array<int, size>> &v) {
	const int n = (int) v.size();

	std::vector<int> order(n);
	std::iota(order.begin(), order.end(), 0);

	for (int i = (int) size - 1; i >= 0; i--) {
		std::vector<int> buckets(m);
		for (int j = 0; j < n; j++) {
			assert(0 <= v[j][i] && v[j][i] < m);
			buckets[v[j][i]]++;
		}

		for (int j = 1; j < m; j++) {
			buckets[j] += buckets[j - 1];
		}
		
		std::vector<int> new_order(n);
		for (int j = n - 1; j >= 0; j--) {
			new_order[--buckets[v[order[j]][i]]] = order[j];
		}
	
		order.swap(new_order);
	}

	return order;
}

template <std::size_t size>
std::vector<int> radix_sort_rank(int m, const std::vector<std::array<int, size>> &v) {
	auto order = radix_sort_order(m, v);
	std::vector<int> rank(v.size());

	for (int i = 1; i < (int) v.size(); i++) {	
		rank[order[i]] = rank[order[i - 1]];
		if (v[order[i - 1]] < v[order[i]]) {
			rank[order[i]]++;
		}
	}

	return rank;
}

std::vector<int> suffix_array(std::vector<int> w) {
	const int n = (int) w.size();

	if (n < 8) {
		return suffix_array_brute(w);
	}

	w.push_back(-1);
	w.push_back(-1);
	
	std::vector<std::array<int, 3>> w_;
	
	for (int s : {0, 1}) {
		for (int i = s; i < n; i += 3) {
			std::array<int, 3> nr;
			for (int j = 0; j < 3; j++)
				nr[j] = w[i + j] + 1;
			w_.push_back(nr);
		}
		w_.push_back({0, 0, 0});
	}
	w_.pop_back();

	std::vector<int> S01 = suffix_array(radix_sort_rank(n + 1, w_));
	std::vector<int> S01_inv(n + 2);

	S01.erase(S01.begin());

	for (int i = 0; i < (int) S01.size(); i++) {
		int& p = S01[i];

		if (p < (n + 2) / 3) {
			p *= 3;
		}
		else {
			p -= (n + 2) / 3 + 1;
			p *= 3;
			p++;
		}

		S01_inv[p] = i + 1;
	}

	std::vector<std::array<int, 2>> S2_pair(n / 3);
	for (int i = 2; i < n; i += 3) {
		S2_pair[i / 3][0] = w[i];
		S2_pair[i / 3][1] = S01_inv[i + 1];
	}

	std::vector<int> S2 = radix_sort_order(n + 1, S2_pair);
	for (int &i : S2) {
		i = 3 * i + 2;
	}

	std::vector<int> sa;

	int p = 0, q = 0;
	while (p < (int) S2.size() && q < (int) S01.size()) {
		int i = S2[p], j = S01[q];

		std::tuple<int, int, int> L, R;

		if (j % 3 == 0) {
			L = std::make_tuple(w[i], S01_inv[i + 1], -1);
			R = std::make_tuple(w[j], S01_inv[j + 1], -1);
		}
		else {
			L = std::make_tuple(w[i], w[i + 1], S01_inv[i + 2]);
			R = std::make_tuple(w[j], w[j + 1], S01_inv[j + 2]);
		}

		if (L < R) {
			sa.push_back(i);
			p++;
		}
		else {
			sa.push_back(j);
			q++;
		}
	}

	while (p < (int) S2.size())
		sa.push_back(S2[p++]);

	while (q < (int) S01.size())
		sa.push_back(S01[q++]);

	w.pop_back();
	w.pop_back();

	return sa;
}

template <std::size_t max_size>
void test_radix_sort_order(int min_n, int max_n, int seed = 2137) {
	std::cerr << "TEST(radix_sort_order<" << max_size << ">, " << min_n << ", " << max_n << ", " << seed << ")\n";

	std::mt19937 rng(seed);
	
	auto randint = [&](int a, int b) {
		return std::uniform_int_distribution<int>(a, b)(rng);
	};
	
	for (int test = 0; test < 10000; test++) {
		int n = randint(min_n, max_n);
		
		std::vector<std::array<int, max_size>> v(n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < (int) max_size; j++)
				v[i][j] = randint(0, n - 1);

		assert(radix_sort_order(n, v) == brute_sort_order(n, v));
	}

	if constexpr (max_size > 1) {
		test_radix_sort_order<max_size - 1>(min_n, max_n, seed);
	}
}

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

	test_radix_sort_order<10>(1, 10, 1);

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

	test_suffix_array(1, 10, 1);
	test_suffix_array(1, 100, 2);
	test_suffix_array(1, 200, 3);

	test_suffix_array_binary(1, 5, 4);
	test_suffix_array_binary(1, 100, 5);
	test_suffix_array_binary(1, 200, 6);

	return 0;
}
