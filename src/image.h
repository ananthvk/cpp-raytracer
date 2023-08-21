#pragma once
#include <stdint.h>
#include <string>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include <assert.h>

const int CHANNELS = 3;
const double SCALE_FACTOR = 255.99;
// Pixels are represented in floating point format, with values from 0 to 1.0 corresponding to 0 to 255
struct colorf
{
    double r;
    double g;
    double b;
    colorf() : r(0), g(0), b(0) {}
};

using image_row = std::vector<colorf>;
using image = std::vector<image_row>;
// Writes the floating point image data to the file after converting it to integer format.
void write_to_file(const std::string &filename, image img)
{
    size_t height = img.size();
    size_t width = (img.empty()) ? 0 : img[0].size();
    uint8_t *data = new uint8_t[width * height * CHANNELS];

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            data[(i * width + j) * CHANNELS] =
                static_cast<uint8_t>(SCALE_FACTOR * img[i][j].r);
            data[(i * width + j) * CHANNELS + 1] =
                static_cast<uint8_t>(SCALE_FACTOR * img[i][j].g);
            data[(i * width + j) * CHANNELS + 2] =
                static_cast<uint8_t>(SCALE_FACTOR * img[i][j].b);
        }
    }
    stbi_write_png(filename.c_str(), width, height, CHANNELS, data,
                   width * CHANNELS);
    delete data;
}
