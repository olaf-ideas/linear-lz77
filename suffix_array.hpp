#pragma once

#include <vector>
#include <array>
#include <tuple>

#include "radix.hpp"
#include "brute/suffix_array_brute.hpp"

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