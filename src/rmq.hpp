#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

/*
  RMQ based on: https://codeforces.com/blog/entry/78931
*/

template <typename T>
class RangeMinimumQuery {

public:

  RangeMinimumQuery(const std::vector<T> &_v) 
    : v(_v), n((int) v.size()), mask(n), table(n) {
    int curr = 0;
    for (int i = 0; i < n; i++) {
      curr = (curr << 1) & ((1 << block) - 1);

      while (curr > 0 && std::min(v[i], v[i - msb_index(lsb(curr))]) == v[i]) {
        curr ^= lsb(curr);
      }

      curr |= 1;
      mask[i] = curr;
    }

    for (int i = 0; i < n / block; i++) {
      table[i] = small(block * i + block - 1);
    }

    for (int j = 1; (1 << j) <= n / block; j++) {
      for (int i = 0; i + (1 << j) <= n / block; i++) {
        table[n / block * j + i] = std::min(
          table[n / block * (j - 1) + i],
          table[n / block * (j - 1) + i + (1 << (j - 1))]
        );
      }
    }
  }
  
  // [l, r)
  T query(int l, int r) const {
    assert(0 <= l && l < r && r <= n);

    if (r - l <= block) {
      return small(r - 1, r - l);
    }

    T result = std::min(small(l + block - 1), small(r - 1));

    l = l / block + 1;
    r = (r - 1) / block - 1;

    if (l <= r) {
      int j = msb_index(r - l + 1);
      result = std::min(result, std::min(
        table[n / block * j + l],
        table[n / block * j + r - (1 << j) + 1]
      ));
    }

    return result;
  }

private:

  static const int block = 30;

  std::vector<T> v;
  int n;
  std::vector<int> mask;
  std::vector<T> table;

  int lsb(int m) const {
    return m & -m;
  }

  int msb_index(int m) const {
    return __builtin_clz(1) - __builtin_clz(m);
  }

  T small(int r, int size = block) const {
    int dist_from_r = msb_index(mask[r] & ((1 << size) - 1));

    return v[r - dist_from_r];
  }
};