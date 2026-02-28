#include "common.h"
#include <iostream>
#include <chrono>
#include <string>
#include <immintrin.h>

namespace edge {

void edge_detect_explicit(const Image& in, Image& out) {
    const int H = in.height, W = in.width;
    out.width = W;
    out.height = H;
    out.data.assign(W * H, 0.0);
    std::vector<double> gx(W * H, 0.0), gy(W * H, 0.0);

    const double* src = in.data.data();
    double* gx_ptr = gx.data();
    double* gy_ptr = gy.data();

    for (int i = 1; i < H - 1; ++i) {
        int j = 1;
        const int W4 = (W - 2) - ((W - 2) % 4);
        const int j_end = 1 + W4;

        for (; j < j_end; j += 4) {
            __m256d sx = _mm256_setzero_pd();
            __m256d sy = _mm256_setzero_pd();
            const int i0 = (i - 1) * W, i1 = i * W, i2 = (i + 1) * W;

            __m256d k0 = _mm256_set1_pd(SOBEL_X[0]);
            __m256d k1 = _mm256_set1_pd(SOBEL_X[1]);
            __m256d k2 = _mm256_set1_pd(SOBEL_X[2]);
            __m256d a = _mm256_set_pd(src[i0 + j + 3], src[i0 + j + 2], src[i0 + j + 1], src[i0 + j]);
            __m256d b = _mm256_set_pd(src[i0 + j + 4], src[i0 + j + 3], src[i0 + j + 2], src[i0 + j + 1]);
            __m256d c = _mm256_set_pd(src[i0 + j + 5], src[i0 + j + 4], src[i0 + j + 3], src[i0 + j + 2]);
            sx = _mm256_add_pd(_mm256_mul_pd(k0, a), sx);
            sx = _mm256_add_pd(_mm256_mul_pd(k1, b), sx);
            sx = _mm256_add_pd(_mm256_mul_pd(k2, c), sx);

            k0 = _mm256_set1_pd(SOBEL_X[3]); k1 = _mm256_set1_pd(SOBEL_X[4]); k2 = _mm256_set1_pd(SOBEL_X[5]);
            a = _mm256_set_pd(src[i1 + j + 3], src[i1 + j + 2], src[i1 + j + 1], src[i1 + j]);
            b = _mm256_set_pd(src[i1 + j + 4], src[i1 + j + 3], src[i1 + j + 2], src[i1 + j + 1]);
            c = _mm256_set_pd(src[i1 + j + 5], src[i1 + j + 4], src[i1 + j + 3], src[i1 + j + 2]);
            sx = _mm256_add_pd(_mm256_mul_pd(k0, a), sx);
            sx = _mm256_add_pd(_mm256_mul_pd(k1, b), sx);
            sx = _mm256_add_pd(_mm256_mul_pd(k2, c), sx);

            k0 = _mm256_set1_pd(SOBEL_X[6]); k1 = _mm256_set1_pd(SOBEL_X[7]); k2 = _mm256_set1_pd(SOBEL_X[8]);
            a = _mm256_set_pd(src[i2 + j + 3], src[i2 + j + 2], src[i2 + j + 1], src[i2 + j]);
            b = _mm256_set_pd(src[i2 + j + 4], src[i2 + j + 3], src[i2 + j + 2], src[i2 + j + 1]);
            c = _mm256_set_pd(src[i2 + j + 5], src[i2 + j + 4], src[i2 + j + 3], src[i2 + j + 2]);
            sx = _mm256_add_pd(_mm256_mul_pd(k0, a), sx);
            sx = _mm256_add_pd(_mm256_mul_pd(k1, b), sx);
            sx = _mm256_add_pd(_mm256_mul_pd(k2, c), sx);

            k0 = _mm256_set1_pd(SOBEL_Y[0]); k1 = _mm256_set1_pd(SOBEL_Y[1]); k2 = _mm256_set1_pd(SOBEL_Y[2]);
            a = _mm256_set_pd(src[i0 + j + 3], src[i0 + j + 2], src[i0 + j + 1], src[i0 + j]);
            b = _mm256_set_pd(src[i0 + j + 4], src[i0 + j + 3], src[i0 + j + 2], src[i0 + j + 1]);
            c = _mm256_set_pd(src[i0 + j + 5], src[i0 + j + 4], src[i0 + j + 3], src[i0 + j + 2]);
            sy = _mm256_add_pd(_mm256_mul_pd(k0, a), sy);
            sy = _mm256_add_pd(_mm256_mul_pd(k1, b), sy);
            sy = _mm256_add_pd(_mm256_mul_pd(k2, c), sy);

            k0 = _mm256_set1_pd(SOBEL_Y[3]); k1 = _mm256_set1_pd(SOBEL_Y[4]); k2 = _mm256_set1_pd(SOBEL_Y[5]);
            a = _mm256_set_pd(src[i1 + j + 3], src[i1 + j + 2], src[i1 + j + 1], src[i1 + j]);
            b = _mm256_set_pd(src[i1 + j + 4], src[i1 + j + 3], src[i1 + j + 2], src[i1 + j + 1]);
            c = _mm256_set_pd(src[i1 + j + 5], src[i1 + j + 4], src[i1 + j + 3], src[i1 + j + 2]);
            sy = _mm256_add_pd(_mm256_mul_pd(k0, a), sy);
            sy = _mm256_add_pd(_mm256_mul_pd(k1, b), sy);
            sy = _mm256_add_pd(_mm256_mul_pd(k2, c), sy);

k0 = _mm256_set1_pd(SOBEL_Y[6]); k1 = _mm256_set1_pd(SOBEL_Y[7]); k2 = _mm256_set1_pd(SOBEL_Y[8]);
            a = _mm256_set_pd(src[i2 + j + 3], src[i2 + j + 2], src[i2 + j + 1], src[i2 + j]);
            b = _mm256_set_pd(src[i2 + j + 4], src[i2 + j + 3], src[i2 + j + 2], src[i2 + j + 1]);
            c = _mm256_set_pd(src[i2 + j + 5], src[i2 + j + 4], src[i2 + j + 3], src[i2 + j + 2]);
            sy = _mm256_add_pd(_mm256_mul_pd(k0, a), sy);
            sy = _mm256_add_pd(_mm256_mul_pd(k1, b), sy);
            sy = _mm256_add_pd(_mm256_mul_pd(k2, c), sy);

            _mm256_storeu_pd(&gx_ptr[i * W + j], sx);
            _mm256_storeu_pd(&gy_ptr[i * W + j], sy);
        }

        for (; j < W - 1; ++j) {
            double sx = 0, sy = 0;
            for (int di = -1; di <= 1; ++di)
                for (int dj = -1; dj <= 1; ++dj) {
                    sx += in.at(i+di, j+dj) * SOBEL_X[(di+1)*3 + (dj+1)];
                    sy += in.at(i+di, j+dj) * SOBEL_Y[(di+1)*3 + (dj+1)];
                }
            gx[i * W + j] = sx;
            gy[i * W + j] = sy;
        }
    }

    const int N = H * W;
    int i = 0;
    for (; i + 4 <= N; i += 4) {
        __m256d gx_v = _mm256_loadu_pd(&gx_ptr[i]);
        __m256d gy_v = _mm256_loadu_pd(&gy_ptr[i]);
        __m256d gx2 = _mm256_mul_pd(gx_v, gx_v);
        __m256d gy2 = _mm256_mul_pd(gy_v, gy_v);
        __m256d sum = _mm256_add_pd(gx2, gy2);
        __m256d mag = _mm256_sqrt_pd(sum);
        _mm256_storeu_pd(&out.data[i], mag);
    }
    for (; i < N; ++i) {
        out.data[i] = std::sqrt(gx[i]*gx[i] + gy[i]*gy[i]);
    }
}

}  // namespace edge

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << (argv[0] ? argv[0] : "edge_explicit") << " <input.pgm> <output.pgm>\n";
        return 1;
    }
    std::string in_path = argv[1], out_path = argv[2];
    edge::Image in = edge::load_pgm(in_path);
    edge::Image out;
    auto t0 = std::chrono::high_resolution_clock::now();
    edge::edge_detect_explicit(in, out);
    auto t1 = std::chrono::high_resolution_clock::now();
    edge::save_pgm(out_path, out);
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
    std::cout << "Explicit (AVX): " << us << " us\n";
    return 0;
}