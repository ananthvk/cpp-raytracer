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
            data[(i * width + j) * CHANNELS] =
                static_cast<uint8_t>((int)(SCALE_FACTOR * img[i][j].x) % 256);
            data[(i * width + j) * CHANNELS + 1] =
                static_cast<uint8_t>((int)(SCALE_FACTOR * img[i][j].y) % 256);
            data[(i * width + j) * CHANNELS + 2] =
                static_cast<uint8_t>((int)(SCALE_FACTOR * img[i][j].z) % 256);
        }
    }
    stbi_write_png(filename.c_str(), width, height, CHANNELS, data,
                   width * CHANNELS);
    free(data);
}
