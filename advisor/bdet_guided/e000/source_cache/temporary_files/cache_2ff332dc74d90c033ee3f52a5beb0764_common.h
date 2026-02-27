#ifndef EDGE_COMMON_H
#define EDGE_COMMON_H

#include <vector>
#include <cstdint>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace edge {

// PGM (grayscale) image: row-major, height rows of width pixels.
struct Image {
    int width{0};
    int height{0};
    std::vector<double> data;  // grayscale [0,255] as double

    double& at(int y, int x) { return data[y * width + x]; }
    const double& at(int y, int x) const { return data[y * width + x]; }
};

// Load PGM (P2 or P5). Converts to double in [0,255].
inline Image load_pgm(const std::string& path) {
    std::ifstream f(path, std::ios::binary);
    if (!f) throw std::runtime_error("Cannot open " + path);
    std::string magic;
    f >> magic;
    int w, h, maxval;
    f >> w >> h >> maxval;
    if (magic != "P2" && magic != "P5") throw std::runtime_error("Unsupported PGM format");
    Image img;
    img.width = w;
    img.height = h;
    img.data.resize(w * h);
    if (magic == "P2") {
        for (int i = 0; i < w * h; ++i) {
            int v; f >> v;
            img.data[i] = static_cast<double>(v);
        }
    } else {
        f.get();  // newline after maxval
        for (int i = 0; i < w * h; ++i) {
            unsigned char v;
            f.read(reinterpret_cast<char*>(&v), 1);
            img.data[i] = static_cast<double>(static_cast<unsigned>(v));
        }
    }
    return img;
}

// Save PGM P2 (ASCII) for portability.
inline void save_pgm(const std::string& path, const Image& img) {
    std::ofstream f(path);
    if (!f) throw std::runtime_error("Cannot write " + path);
    f << "P2\n" << img.width << " " << img.height << "\n255\n";
    for (int i = 0; i < img.height * img.width; ++i) {
        int v = static_cast<int>(std::round(std::max(0., std::min(255., img.data[i]))));
        f << v << ( (i + 1) % img.width == 0 ? "\n" : " " );
    }
}

// Sobel 3x3 kernels (flattened row-major for convenience).
constexpr double SOBEL_X[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
constexpr double SOBEL_Y[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };

}  // namespace edge

#endif
