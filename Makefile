CXX = g++
CXXFLAGS = -std=c++20 -O2
# CXXFLAGS = -std=c++20 -Wall -Wshadow -g -fsanitize=undefined,address

SRC_DIR = src
TEST_DIR = test
BENCH_DIR = bench
BIN_DIR = bin

MAIN_SRC = $(SRC_DIR)/main.cpp
MAIN_BIN = $(BIN_DIR)/main

TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_BINS = $(patsubst $(TEST_DIR)/%.cpp, $(BIN_DIR)/%, $(TEST_SRCS))

BENCH_SRCS = $(wildcard $(BENCH_DIR)/*.cpp)
BENCH_BINS = $(patsubst $(BENCH_DIR)/%.cpp, $(BIN_DIR)/%, $(BENCH_SRCS))

all: $(MAIN_BIN) tests benchs

$(MAIN_BIN): $(MAIN_SRC)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BIN_DIR)/%: $(TEST_DIR)/%.cpp
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BIN_DIR)/%: $(BENCH_DIR)/%.cpp
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

run-tests: tests
	@for test in $(TEST_BINS); do \
		echo "Running $$test..."; \
		./$$test || exit 1; \
	done
	@echo "All tests passed!"

run-benchs: benchs
	@for bench in $(BENCH_BINS); do \
		echo "Running $$bench..."; \
		./$$bench || exit 1; \
	done
	@echo "All benchmarks finished!"

tests: $(TEST_BINS)

benchs: $(BENCH_BINS)

clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean tests benchs run-tests run-bench