cmake_minimum_required(VERSION 3.16)
project(edge_detection LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Intel oneAPI: use icpx if available, else fallback to system compiler
if(DEFINED ENV{ONEAPI_ROOT})
  set(CMAKE_CXX_COMPILER "icpx" CACHE STRING "Intel oneAPI C++ compiler")
endif()

# Auto vectorization: rely on compiler -O3 -march=native
add_executable(edge_auto edge_auto.cpp)
target_include_directories(edge_auto PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(edge_auto PROPERTIES
  COMPILE_OPTIONS "-O3 -march=native"
)

# Implicit: OpenMP SIMD (Intel -qopenmp or -fiopenmp)
add_executable(edge_implicit edge_implicit.cpp)
target_include_directories(edge_implicit PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(edge_implicit PRIVATE -O3 -march=native)
target_link_options(edge_implicit PRIVATE $<$<CXX_COMPILER_ID:IntelLLVM>:-fiopenmp> $<$<CXX_COMPILER_ID:GNU>:-fopenmp> $<$<CXX_COMPILER_ID:Clang>:-fopenmp> $<$<CXX_COMPILER_ID:Intel>:-qopenmp>)

# Explicit: AVX2 intrinsics
add_executable(edge_explicit edge_explicit.cpp)
target_include_directories(edge_explicit PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(edge_explicit PROPERTIES
  COMPILE_OPTIONS "-O3 -march=native"
)
