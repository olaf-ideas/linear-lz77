#include <iostream>
#include <chrono>
#include <random>
#include <cassert>
#include <fstream>
#include <sstream>
#include <string>

#include "../src/lz77.hpp"


void bench_lz77(int n, int seed = 2137) {
	std::cerr << "BENCH(bench_lz77, " << n << ")\n";
	std::mt19937 rng(seed);
	std::uniform_int_distribution<int> dist('a', 'z');

	std::vector<int> w(n);
	for (int &c : w) {
		c = dist(rng);
		assert(0 <= c && c < n);
	}

	auto start = std::chrono::high_resolution_clock::now();
	auto w_lz77 = lz77(w);
	auto end = std::chrono::high_resolution_clock::now();

	double elapsed = std::chrono::duration<double, std::milli>(end - start).count();

	std::cout << "n: " << n << " => " << elapsed << " ms avg: " << elapsed / n << " ms\n";
	std::cerr << "lz size: " << w_lz77.size() << " => " << (double) w_lz77.size() / w.size() << "% of original" << '\n';
}

void bench_lz77_pan_tadeusz(int seed = 2137) {
	std::cerr << "BENCH(bench_lz77_pan_tadeusz)\n";

	std::ifstream input("./bench/pantadeusz.txt");
	assert(input.is_open());

	std::ostringstream buffer;

	buffer << input.rdbuf();

	std::string PanTadeusz = buffer.str();

	std::vector<int> w;

	for (char c : PanTadeusz) {
		w.push_back((int) c + 255);
		assert(0 <= w.back() && w.back() < (int) PanTadeusz.size());
	}

	std::cerr << "File length: " << w.size() << '\n';

	auto start = std::chrono::high_resolution_clock::now();
	auto w_lz77 = lz77(w);
	auto end = std::chrono::high_resolution_clock::now();

	assert(w == unroll_lz77(w_lz77));

	double elapsed = std::chrono::duration<double, std::milli>(end - start).count();

	std::cout << "n: " << w.size() << " => " << elapsed << " ms avg: " << elapsed / w.size() << " ms\n";
	std::cerr << "lz size: " << w_lz77.size() << " => " << (double) w_lz77.size() / w.size() << "% of original" << '\n';
}

int main() {

	for (int n = 1000; n < 10000000; n *= 2) {
	  bench_lz77(n);
	}

	bench_lz77_pan_tadeusz();

	return 0;
}