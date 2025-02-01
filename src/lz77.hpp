#pragma once

#include <vector>
#include <tuple>
#include <limits>

#include "suffix_array.hpp"
#include "lcp.hpp"
#include "rmq.hpp"

std::vector<std::tuple<int, int, int>> lz77(const std::vector<int> &w) {
  const int n = (int) w.size();

  std::vector<int> sa = suffix_array(w);
  std::vector<int> sa_inv(n);
  for (int i = 0; i < n; i++)
    sa_inv[sa[i]] = i;
  
  std::vector<int> lcp = longest_common_prefix(w, sa);
  
  RangeMinimumQuery<int> rmq(lcp);

  std::vector<int> next(n, -1), prev(n, -1);

  for (int i = 1; i < n; i++) {
    next[sa[i - 1]] = sa[i];
    prev[sa[i]] = sa[i - 1];
  }

  std::vector<std::pair<int, int>> lpf(n);
  for (int i = n - 1; i >= 0; i--) {
    if (next[i] != -1) {
      lpf[i] = std::max(lpf[i], 
        std::make_pair(rmq.query(sa_inv[i], sa_inv[next[i]]), next[i])
      );
      prev[next[i]] = prev[i];
    }

    if (prev[i] != -1) {
      lpf[i] = std::max(lpf[i], 
        std::make_pair(rmq.query(sa_inv[prev[i]], sa_inv[i]), prev[i])
      );
      next[prev[i]] = next[i];
    }
  }

  std::vector<std::tuple<int, int, int>> w_lz77;
  for (int i = 0; i < n; ) {
    auto [len, pos] = lpf[i];

    if (i + len == n) {
      len--;
    }

    if (len == 0) {
      pos = 0;
    }

    w_lz77.emplace_back(pos, len, w[i + len]);
    i += len + 1;
  }

  return w_lz77;
}

std::vector<int> unroll_lz77(const std::vector<std::tuple<int, int, int>> &w_lz77, int expected_length = 1'000'000) {
  std::vector<int> w;

  for (auto [pos, len, c] : w_lz77) {
    assert(len >= 0);

    if (len > 0) {
      assert(0 <= pos && pos < (int) w.size());
      assert((int) w.size() + len < expected_length);

      while (len--) {
        w.push_back(w[pos++]);
      }
    }

    w.push_back(c);
  }

  return w;
}