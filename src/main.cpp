#include "image.h"
#include <iostream>

const int image_width = 256;
const int image_height = 256;

int main()
{
    try
    {
        image img(image_height, image_row(image_width, colorf()));
        for (int j = 0; j < image_height; ++j)
        {
            for (int i = 0; i < image_width; ++i)
            {
                img[j][i].r = double(i) / (image_width - 1);
                img[j][i].g = double(j) / (image_height - 1);
                img[j][i].b = 0;
            }
        }
        write_to_file("test.png", img);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}