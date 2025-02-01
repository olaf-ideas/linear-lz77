# Implementation of LZ77 with linear complexity

## Project Structure

```
.
├── bench/
│   ├── bench_suffix_array.cpp
│   └── bench_lz77.cpp
├── bin/
├── brute/ # Brute-force of every algorithm block
├── src/   # Source of the algorithm
│   ├── main.cpp
│   ├── lcp.hpp
│   ├── rmq.hpp
│   ├── lz77.hpp
│   ├── radix.hpp
│   └── suffix_array.hpp
├── test/  # Simple fuzzing
│   ├── test_lz77.cpp
│   ├── test_radix.cpp
│   └── test_suffix_array.cpp
├── Makefile
└── README.md
```

## Build Instructions

### Compile Everything
```bash
make
```

### Clean Build Files
```bash
make clean
```

## Running Tests / Benchmarks

Run all tests:
```bash
make run-tests
```

Run all benchmarks:
```bash
make run-benchs
```

## Benchmark Results

The benchmark measures the **total construction time** and the **average time per character**. Here are local results (for 'a' to 'z' alphabet):

```
BENCH(suffix_array, 1024000)
n: 1024000 => 243.215 ms avg: 0.000237515 ms
BENCH(suffix_array, 2048000)
n: 2048000 => 688.389 ms avg: 0.000336127 ms
BENCH(suffix_array, 4096000)
n: 4096000 => 1634.21 ms avg: 0.000398976 ms
BENCH(suffix_array, 8192000)
n: 8192000 => 4679.19 ms avg: 0.000571191 ms


BENCH(bench_lz77, 4096000)
n: 4096000 => 2662.11 ms avg: 0.00064993 ms
lz size: 815532 => 0.199104% of original
BENCH(bench_lz77, 8192000)
n: 8192000 => 6232.97 ms avg: 0.000760861 ms
lz size: 1571227 => 0.1918% of original


BENCH(bench_lz77_pan_tadeusz)
File length: 476840
n: 476840 => 126.146 ms avg: 0.000264545 ms
lz size: 66449 => 0.139353% of original
```