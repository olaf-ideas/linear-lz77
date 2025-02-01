#include <iostream>
#include <chrono>
#include <random>
#include <cassert>

#include "../src/suffix_array.hpp"


void bench_suffix_array(int n, int seed = 2137) {
  std::cerr << "BENCH(suffix_array, " << n << ")\n";
  std::mt19937 rng(seed);
  std::uniform_int_distribution<int> dist('a', 'z');

  std::vector<int> w(n);
  for (int &c : w) {
    c = dist(rng);
    assert(0 <= c && c < n);
  }

  auto start = std::chrono::high_resolution_clock::now();
  auto sa = suffix_array(w);
  auto end = std::chrono::high_resolution_clock::now();

  double elapsed = std::chrono::duration<double, std::milli>(end - start).count();

  std::cout << "n: " << n << " => " << elapsed << " ms avg: " << elapsed / n << " ms\n";
}

int main() {

  for (int n = 1000; n < 10000000; n *= 2) {
    bench_suffix_array(n);
  }

  return 0;
}