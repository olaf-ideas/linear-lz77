#pragma once

#include <vector>
#include <algorithm>
#include <numeric>

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