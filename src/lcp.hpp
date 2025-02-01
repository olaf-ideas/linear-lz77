#pragma once

#include <vector>
#include <algorithm>

#include "suffix_array.hpp"


std::vector<int> longest_common_prefix(std::vector<int> w, const std::vector<int> &sa) {
  const int n = (int) w.size();
  w.push_back(-1);

  std::vector<int> lcp(n - 1);
  std::vector<int> sa_inv(n);

  for (int i = 0; i < n; i++) {
    sa_inv[sa[i]] = i;
  }

  int k = 0;
  for (int i = 0; i < n - 1; i++) {
    if (sa_inv[i] == n - 1) {
      k = 0;
      continue;
    }

    k = std::max(0, k - 1);

    int j = sa[sa_inv[i] + 1];
    while (w[i + k] == w[j + k]) {
      k++;
    }

    lcp[sa_inv[i]] = k;
  }

  return lcp;
}