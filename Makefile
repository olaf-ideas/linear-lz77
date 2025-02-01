CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wshadow -g -fsanitize=undefined,address

SRC_DIR = .
TEST_DIR = test
BIN_DIR = bin

MAIN_SRC = $(SRC_DIR)/main.cpp
MAIN_BIN = $(BIN_DIR)/main

TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_BINS = $(patsubst $(TEST_DIR)/%.cpp, $(BIN_DIR)/%, $(TEST_SRCS))

all: $(MAIN_BIN) tests

$(MAIN_BIN): $(MAIN_SRC)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BIN_DIR)/%: $(TEST_DIR)/%.cpp
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

run-tests: tests
	@for test in $(TEST_BINS); do \
		echo "Running $$test..."; \
		./$$test || exit 1; \
	done
	@echo "All tests passed!"

tests: $(TEST_BINS)

clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean tests run-tests
