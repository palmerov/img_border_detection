# Edge Detection — Python & C++ (Intel oneAPI)

Gradient magnitude edge detection: **G[i] = √(Gx[i]² + Gy[i]²)** using Sobel kernels. No OpenCV or other ready-made edge detectors; only basic image I/O, NumPy (Python), and hand-written C++ with three vectorization strategies.

## Project layout

| Folder   | Contents |
|----------|----------|
| **python/** | Jupyter notebook + helpers: edge detection from scratch (NumPy, PIL, matplotlib). |
| **cpp/**    | C++ implementation with **auto**, **implicit** (OpenMP SIMD), and **explicit** (AVX2) vectorization for Intel oneAPI. |

## Quick start

### Python

```bash
cd python
pip install -r requirements.txt
jupyter notebook edge_detection.ipynb
```

Run all cells. Optionally put `test_image.png` in `python/` to use your own image.

### C++ (Intel oneAPI)

```bash
cd cpp
# Generate test PGM from Python
python ../python/export_pgm.py
# Build (requires icpx or g++ with OpenMP/AVX2)
make
./edge_auto input.pgm out_auto.pgm
./edge_implicit input.pgm out_implicit.pgm
./edge_explicit input.pgm out_explicit.pgm
```

See `python/README.md` and `cpp/README.md` for details.
