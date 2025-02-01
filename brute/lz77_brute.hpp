#pragma once

#include <vector>
#include <tuple>

std::vector<std::tuple<int, int, int>> lz77_brute(std::vector<int> w) {
  std::vector<std::tuple<int, int, int>> w_lz77;

  for (int i = 0; i < (int) w.size(); i++) {
    int best_pos = 0;
    int best_len = 0;

    for (int j = 0; j < i; j++) {
      int match = 0;

      while (i + match + 1 < (int) w.size() && w[i + match] == w[j + match]) {
        match++;
      }

      if (match > best_len) {
        best_pos = j;
        best_len = match;
      }
    }

    w_lz77.emplace_back(best_pos, best_len, w[i + best_len]);
    i += best_len;
  }

  return w_lz77;
}