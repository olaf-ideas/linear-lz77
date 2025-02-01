#pragma once

#include <vector>
#include <algorithm>

template <typename T>
class RangeMinimumQueryBrute {

public:

  RangeMinimumQueryBrute(const std::vector<T> &_v) :
    v(_v), n((int) v.size()) {
    
  }

  T query(int l, int r) {
    T result = v[l];

    for (int i = l + 1; i < r; i++) {
      result = std::min(result, v[i]);
    }
    
    return result;
  }

private:

  std::vector<T> v;
  int n;

};