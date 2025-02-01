#pragma once

#include <vector>
#include <array>
#include <algorithm>
#include <numeric>

template <std::size_t size>
std::vector<int> radix_sort_order_brute(int, const std::vector<std::array<int, size>> &v) {
	std::vector<int> order(v.size());
	std::iota(order.begin(), order.end(), 0);
	std::sort(order.begin(), order.end(),
		[&](int i, int j) {
			return v[i] < v[j];
		}
	);

	return order;
}