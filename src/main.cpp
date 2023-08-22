#include "camera.hpp"
#include "colors.hpp"
#include "image.hpp"
#include "progressbar.hpp"
#include <iostream>

const int image_width = 640;
const int image_height = 360;
const int PROGRESSBAR_WIDTH = 40;

colorf raytrace(int row, int col, const Ray &ray)
{
    auto r = ray.direction();
    colorf result;
    double t = double(row) / (image_height - 1);
    return lerp(SKY_COLOR, LIGHT_SKY, t);
}

int main()
{
    int k = 0;
    int max_val = image_height;
    RegularCamera cam(image_width, image_height);
    cam.debug_info(std::cout);
    // TODO: Set VT terminal when compiling on windows
    progressbar_hide_cursor();
    progressbar_display(std::cout, k, max_val, PROGRESSBAR_WIDTH);
    try
    {
        image img(image_height, image_row(image_width, colorf()));
        for (int i = 0; i < image_height; ++i)
        {
            for (int j = 0; j < image_width; ++j)
            {
                img[i][j] = raytrace(i, j, cam.get_ray(i, j));
            }
            ++k;
            progressbar_display(std::cout, k, max_val, PROGRESSBAR_WIDTH);
        }
        std::cout << std::endl;
        progressbar_show_cursor();
        write_to_file("test.png", img);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}