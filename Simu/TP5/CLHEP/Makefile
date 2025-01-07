CXX := g++-14
CXXFLAGS := -std=c++17 -Wall -I/opt/homebrew/include
LDFLAGS := -L/opt/homebrew/lib -lCLHEP

OMP_FLAGS := -fopenmp

BUILD_DIR := build
SRC_DIR := .
DATA_DIR := data

$(shell mkdir -p $(BUILD_DIR) $(DATA_DIR))

SINGLE_SRC := Single-Thread_Monte-Carlo.cpp
MULTI_SRC := Multi-Thread_Monte-Carlo.cpp
OPENMP_SRC := OpenMP-Monte_Carlo.cpp
CHECK_SRC := checkStatus.cpp

SINGLE_OBJ := $(BUILD_DIR)/Single-Thread_Monte-Carlo.o
MULTI_OBJ := $(BUILD_DIR)/Multi-Thread_Monte-Carlo.o
OPENMP_OBJ := $(BUILD_DIR)/OpenMP-Monte_Carlo.o
CHECK_OBJ := $(BUILD_DIR)/checkStatus.o

HEADERS := status.hpp monte_carlo.hpp

SINGLE_EXE := $(BUILD_DIR)/Single-Thread_Monte-Carlo
MULTI_EXE := $(BUILD_DIR)/Multi-Thread_Monte-Carlo
OPENMP_EXE := $(BUILD_DIR)/OpenMP-Monte_Carlo
CHECK_EXE := $(BUILD_DIR)/checkStatus

TARGETS := $(SINGLE_EXE) $(MULTI_EXE) $(OPENMP_EXE) $(CHECK_EXE)

.PHONY: all clean debug

all: $(TARGETS)

$(SINGLE_OBJ): $(SINGLE_SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(MULTI_OBJ): $(MULTI_SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OPENMP_OBJ): $(OPENMP_SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(OMP_FLAGS) -c $< -o $@

$(CHECK_OBJ): $(CHECK_SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(SINGLE_EXE): $(SINGLE_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(MULTI_EXE): $(MULTI_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) -pthread

$(OPENMP_EXE): $(OPENMP_OBJ)
	$(CXX) $(CXXFLAGS) $(OMP_FLAGS) $^ -o $@ $(LDFLAGS)

$(CHECK_EXE): $(CHECK_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)/*
	@echo "Cleaned build directory"

debug:
	@echo "Compiler: $(CXX)"
	@echo "Compiler flags: $(CXXFLAGS)"
	@echo "OpenMP flags: $(OMP_FLAGS)"
	@echo "Linker flags: $(LDFLAGS)"
	@echo "Source files:"
	@echo "  SINGLE_SRC: $(SINGLE_SRC)"
	@echo "  MULTI_SRC: $(MULTI_SRC)"
	@echo "  OPENMP_SRC: $(OPENMP_SRC)"
	@echo "  CHECK_SRC: $(CHECK_SRC)"
	@echo "Object files:"
	@echo "  SINGLE_OBJ: $(SINGLE_OBJ)"
	@echo "  MULTI_OBJ: $(MULTI_OBJ)"
	@echo "  OPENMP_OBJ: $(OPENMP_OBJ)"
	@echo "  CHECK_OBJ: $(CHECK_OBJ)"