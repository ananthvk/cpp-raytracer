#include "camera.hpp"
#include "colors.hpp"
#include "config.h"
#include "frombook.hpp"
#include "image.hpp"
#include "progressbar.hpp"
#include "scene.hpp"
#include <iostream>

int main()
{
    // Seed the random number generator
    // srand((unsigned)time(NULL));
    int k = 0;
    int max_val = IMAGE_HEIGHT;
    MovableCamera cam;
    Scene scene;
    cam.debug_info(std::cout);
    // TODO: Set VT terminal when compiling on windows
    progressbar_hide_cursor();
    progressbar_display(std::cout, k, max_val, PROGRESSBAR_WIDTH);
    try
    {
        image img(IMAGE_HEIGHT, image_row(IMAGE_WIDTH, color()));
        for (int i = 0; i < IMAGE_HEIGHT; ++i)
        {
            for (int j = 0; j < IMAGE_WIDTH; ++j)
            {
                color pixel_color(0, 0, 0);
                for (int sample = 0; sample < SAMPLES_PER_PIXEL; ++sample)
                {
                    auto ray = cam.get_ray(i, j, SAMPLES_PER_PIXEL > 1);
                    pixel_color += scene.color_at(ray, RECURSION_LIMIT);
                }
                pixel_color /= SAMPLES_PER_PIXEL;
                pixel_color = gamma_correction(pixel_color, 2); // Apply gamma 2
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