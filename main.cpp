#include <eigen3/Eigen/StdVector>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include <iostream>
int main()
{
    Eigen::Vector3d v(3, 4, 5);
    Eigen::Vector3d v2;
    v2 = v.normalized();
    std::cout << v2 << std::endl;
    std::cout << v.norm() << std::endl;
    std::cout << "Hello raytracer!";
    const int channels = 3;
    const int width = 100;
    const int height = 100;
    unsigned char *data = new unsigned char[width * height * channels]();
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            // R G
            // B W
            if (i <= height / 2 && j <= width / 2)
            {
                data[(i * width + j) * channels] = 255;
                data[(i * width + j) * channels + 1] = 0;
                data[(i * width + j) * channels + 2] = 0;
            }
            else if (i <= height / 2 && j > width / 2)
            {
                data[(i * width + j) * channels] = 0;
                data[(i * width + j) * channels + 1] = 255;
                data[(i * width + j) * channels + 2] = 0;
            }
            else if (i > height / 2 && j <= width / 2)
            {
                data[(i * width + j) * channels] = 0;
                data[(i * width + j) * channels + 1] = 0;
                data[(i * width + j) * channels + 2] = 255;
            }
            else if (i > height / 2 && j > width / 2)
            {
                data[(i * width + j) * channels] = 255;
                data[(i * width + j) * channels + 1] = 255;
                data[(i * width + j) * channels + 2] = 255;
            }
        }
    }

    stbi_write_png("test.png", width, height, channels, data, width * channels);
    delete data;
    return 0;
}