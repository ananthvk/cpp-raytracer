#include "camera.hpp"
#include "colors.hpp"
#include "image.hpp"
#include "progressbar.hpp"
#include "scene.hpp"
#include <iostream>

const int image_width = 400;
const int image_height = 225;
const int PROGRESSBAR_WIDTH = 40;
const int SAMPLES_PER_PIXEL = 10; // NOTE: MUST BE NON-ZERO AND POSITIVE
const int RECURSION_LIMIT = 50;

int main()
{
    int k = 0;
    int max_val = image_height;
    RegularCamera cam(image_width, image_height);
    Scene scene;
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
                colorf pixel_color(0, 0, 0);
                for (int sample = 0; sample < SAMPLES_PER_PIXEL; ++sample)
                {
                    auto ray = cam.get_ray(i, j, SAMPLES_PER_PIXEL > 1);
                    pixel_color +=
                        scene.color_at(ray, i, j, image_width, image_height, RECURSION_LIMIT);
                }
                pixel_color /= SAMPLES_PER_PIXEL;
                img[i][j] = pixel_color;
            }
            ++k;
            progressbar_display(std::cout, k, max_val, PROGRESSBAR_WIDTH);
        }
        std::cout << std::endl;
        progressbar_show_cursor();
        std::cout << "Writing to disk....." << std::endl;
        write_to_file("output.png", img);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}