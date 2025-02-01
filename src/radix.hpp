#pragma once

#include <vector>
#include <array>
#include <numeric>

template <std::size_t size>
std::vector<int> radix_sort_order(int m, const std::vector<std::array<int, size>> &v) {
	const int n = (int) v.size();

	std::vector<int> order(n);
	std::iota(order.begin(), order.end(), 0);

	for (int i = (int) size - 1; i >= 0; i--) {
		std::vector<int> buckets(m);
		for (int j = 0; j < n; j++) {
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