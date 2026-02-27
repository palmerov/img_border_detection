#!/usr/bin/env python3
"""
Export a grayscale image to PGM (P2) for use with the C++ edge detection programs.
Usage: python export_pgm.py [image.png] [output.pgm]
       If no args: creates a synthetic 256x256 and writes ../cpp/input.pgm
"""

import sys
import os
import numpy as np
from PIL import Image

def to_pgm(path_out, gray_array):
    h, w = gray_array.shape
    with open(path_out, "w") as f:
        f.write(f"P2\n{w} {h}\n255\n")
        for row in gray_array:
            row_int = np.clip(np.round(row), 0, 255).astype(np.int32)
            f.write(" ".join(map(str, row_int)) + "\n")

def main():
    if len(sys.argv) >= 3:
        img = Image.open(sys.argv[1]).convert("L")
        arr = np.array(img)
        to_pgm(sys.argv[2], arr)
        print(f"Written {sys.argv[2]} ({arr.shape[1]}x{arr.shape[0]})")
    else:
        # Synthetic 256x256
        size = 256
        y = np.linspace(-1, 1, size)
        x = np.linspace(-1, 1, size)
        xx, yy = np.meshgrid(x, y)
        circle = (xx**2 + yy**2 < 0.5**2).astype(np.float64) * 255
        rect = np.zeros((size, size), dtype=np.float64)
        a, b = size // 4, 3 * size // 4
        rect[a:b, a:b] = 180
        gray = np.clip(circle * 0.6 + rect * 0.4, 0, 255)
        cpp_dir = os.path.join(os.path.dirname(__file__), "..", "cpp")
        out = os.path.join(cpp_dir, "input.pgm")
        os.makedirs(cpp_dir, exist_ok=True)
        to_pgm(out, gray)
        print(f"Written synthetic image to {out} ({size}x{size})")

if __name__ == "__main__":
    main()
