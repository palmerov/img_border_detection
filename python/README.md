# Python Edge Detection

Gradient magnitude edge detection from scratch: \( G[i] = \sqrt{G_x[i]^2 + G_y[i]^2} \) using Sobel kernels. Uses only NumPy, Pillow, and matplotlib (no OpenCV or other edge-detection libraries).

## Setup

```bash
pip install -r requirements.txt
```

## Run

Open `edge_detection.ipynb` in Jupyter and run all cells. Optionally place a `test_image.png` in this folder to use your own image; otherwise a synthetic test image is used.
