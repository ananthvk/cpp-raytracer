#include "colors.hpp"
#include "image.hpp"
#include "progressbar.hpp"
#include <iostream>

const int image_width = 256;
const int image_height = 256;
const int PROGRESSBAR_WIDTH = 40;

int main()
{
    int k = 0;
    int max_val = image_height * image_width;
    print_progressbar(std::cout, k, max_val, PROGRESSBAR_WIDTH);
    try
    {
        image img(image_height, image_row(image_width, colorf()));
        for (size_t j = 0; j < image_height; ++j)
        {
            for (size_t i = 0; i < image_width; ++i)
            {
                double t = double(j) / (image_height - 1);
                img[j][i] = lerp(SKY_COLOR, LIGHT_SKY, t);
                print_progressbar(std::cout, k, max_val, PROGRESSBAR_WIDTH);
                ++k;
            }
        }
        std::cout << std::endl;
        write_to_file("test.png", img);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}