// Detección de bordes (Sobel). Auto-vectorización del compilador.

#include "common.h"
#include <iostream>
#include <chrono>

namespace edge {

void edge_detect_auto(const Image& in, Image& out) {
    const int H = in.height, W = in.width;
    out.width = W;
    out.height = H;
    out.data.assign(W * H, 0.0);
    std::vector<double> gx(W * H, 0.0), gy(W * H, 0.0);

    for (int i = 1; i < H - 1; ++i) {
        for (int j = 1; j < W - 1; ++j) {
            double sx = 0, sy = 0;
            sx += in.at(i-1, j-1) * SOBEL_X[0] + in.at(i-1, j) * SOBEL_X[1] + in.at(i-1, j+1) * SOBEL_X[2];
            sx += in.at(i,   j-1) * SOBEL_X[3] + in.at(i,   j) * SOBEL_X[4] + in.at(i,   j+1) * SOBEL_X[5];
            sx += in.at(i+1, j-1) * SOBEL_X[6] + in.at(i+1, j) * SOBEL_X[7] + in.at(i+1, j+1) * SOBEL_X[8];
            sy += in.at(i-1, j-1) * SOBEL_Y[0] + in.at(i-1, j) * SOBEL_Y[1] + in.at(i-1, j+1) * SOBEL_Y[2];
            sy += in.at(i,   j-1) * SOBEL_Y[3] + in.at(i,   j) * SOBEL_Y[4] + in.at(i,   j+1) * SOBEL_Y[5];
            sy += in.at(i+1, j-1) * SOBEL_Y[6] + in.at(i+1, j) * SOBEL_Y[7] + in.at(i+1, j+1) * SOBEL_Y[8];
            gx[i * W + j] = sx;
            gy[i * W + j] = sy;
        }
    }

    for (int i = 0; i < H * W; ++i) {
        out.data[i] = std::sqrt(gx[i] * gx[i] + gy[i] * gy[i]);
    }
}

}  // namespace edge

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << (argv[0] ? argv[0] : "edge_auto") << " <input.pgm> <output.pgm>\n";
        return 1;
    }
    std::string in_path = argv[1], out_path = argv[2];
    edge::Image in = edge::load_pgm(in_path);
    edge::Image out;
    auto t0 = std::chrono::high_resolution_clock::now();
    edge::edge_detect_auto(in, out);
    auto t1 = std::chrono::high_resolution_clock::now();
    edge::save_pgm(out_path, out);
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
    std::cout << "Auto vectorization: " << us << " us\n";
    return 0;
}
