# Edge detection C++ — Intel oneAPI vectorization (auto, implicit, explicit)
# Compiler: icpx (oneAPI) or g++/clang++ with OpenMP and AVX2 support

CXX ?= icpx
CXXFLAGS = -std=c++17 -O3 -march=native -I.
OMPFLAG = -fiopenmp   # Intel oneAPI; use -fopenmp for GCC/Clang

.PHONY: all clean run_scalar run_auto run_implicit run_explicit

# Escalar: sin auto-vectorización. GCC: -fno-tree-vectorize; Clang/icpx: -fno-vectorize
SCALAR_FLAGS ?= -std=c++17 -O2 -I. -fno-tree-vectorize

all: edge_scalar edge_auto edge_implicit edge_explicit

edge_scalar: edge_scalar.cpp common.h
	$(CXX) $(SCALAR_FLAGS) -o $@ edge_scalar.cpp

edge_auto: edge_auto.cpp common.h
	$(CXX) $(CXXFLAGS) -o $@ edge_auto.cpp

edge_implicit: edge_implicit.cpp common.h
	$(CXX) $(CXXFLAGS) $(OMPFLAG) -o $@ edge_implicit.cpp

edge_explicit: edge_explicit.cpp common.h
	$(CXX) $(CXXFLAGS) -o $@ edge_explicit.cpp

clean:
	rm -f edge_scalar edge_auto edge_implicit edge_explicit

# Ejemplo: make run_scalar INPUT=../img/input.pgm
run_scalar: edge_scalar
	./edge_scalar $(INPUT) out_scalar.pgm
run_auto: edge_auto
	./edge_auto $(INPUT) out_auto.pgm
run_implicit: edge_implicit
	./edge_implicit $(INPUT) out_implicit.pgm
run_explicit: edge_explicit
	./edge_explicit $(INPUT) out_explicit.pgm
run_implicit: edge_implicit
	./edge_implicit $(INPUT) out_implicit.pgm
run_explicit: edge_explicit
	./edge_explicit $(INPUT) out_explicit.pgm
