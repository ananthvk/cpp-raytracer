// MIT License
// 
// Copyright (c) 2023 Ananthanarayanan Venkitakrishnan (https://github.com/ananthvk)
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#include "image.hpp"
// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void write_to_file(const std::string &filename, image img)
{
    size_t height = img.size();
    size_t width = (img.empty()) ? 0 : img[0].size();
    uint8_t *data = static_cast<uint8_t *>(malloc(width * height * CHANNELS));
    if (data == NULL)
    {
        // Note: TODO: Try to save the float pixel data before exiting to save
        // the rendered image.
        std::cerr << "Error while allocating memory for image!\n";
        exit(1);
    }
    memset(data, 0, width * height * CHANNELS);

    for (size_t i = 0; i < height; ++i)
    {
        for (size_t j = 0; j < width; ++j)
        {
            // Convert from floating point representation to RGB[0, 255]
            data[(i * width + j) * CHANNELS] =
                static_cast<uint8_t>((int)(SCALE_FACTOR * img[i][j].x) % 256);
            data[(i * width + j) * CHANNELS + 1] =
                static_cast<uint8_t>((int)(SCALE_FACTOR * img[i][j].y) % 256);
            data[(i * width + j) * CHANNELS + 2] =
                static_cast<uint8_t>((int)(SCALE_FACTOR * img[i][j].z) % 256);
        }
    }
    // Write the image to png file
    stbi_write_png(filename.c_str(), width, height, CHANNELS, data,
                   width * CHANNELS);
    free(data);
}
