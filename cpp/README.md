# C++ Edge Detection — Intel oneAPI Vectorization

Gradient magnitude edge detection: \( G[i] = \sqrt{G_x[i]^2 + G_y[i]^2} \) with Sobel kernels. Three variants:

| Variant   | File            | Vectorization |
|----------|-----------------|----------------|
| **Auto** | `edge_auto`     | Compiler auto-vectorization (`-O3 -march=native`) |
| **Implicit** | `edge_implicit` | OpenMP SIMD (`#pragma omp simd`) |
| **Explicit** | `edge_explicit` | Intel AVX2 intrinsics |

## Requirements

- Intel oneAPI (recommended): `icpx` in PATH (e.g. `source /opt/intel/oneapi/setvars.sh`).
- Or GCC/Clang with OpenMP and AVX2 (e.g. `g++` with `-fopenmp`).

## Build

**Make (oneAPI):**
```bash
source /opt/intel/oneapi/setvars.sh   # if using oneAPI
make
```

**CMake:**
```bash
mkdir build && cd build
cmake ..
make
```

For GCC instead of icpx: `make CXX=g++ OMPFLAG=-fopenmp`

## Input/Output

Images are **PGM** (portable graymap). Use P2 (ASCII) or P5 (binary).

Create a test PGM from Python (from project root):
```python
import numpy as np
from PIL import Image
img = Image.open("python/test_image.png").convert("L")
arr = np.array(img)
h, w = arr.shape
with open("cpp/input.pgm", "w") as f:
    f.write(f"P2\n{w} {h}\n255\n")
    for row in arr:
        f.write(" ".join(map(str, row)) + "\n")
```

Or use ImageMagick: `convert input.png -compress none input.pgm`

## Run

```bash
./edge_auto     input.pgm out_auto.pgm
./edge_implicit input.pgm out_implicit.pgm
./edge_explicit input.pgm out_explicit.pgm
```

Each program prints the elapsed time in microseconds.
