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
    MovableCamera cam;
    Scene scene;
    ProgressBar progress_bar(IMAGE_HEIGHT, PROGRESSBAR_WIDTH, true);
    cam.debug_info(std::cout);
    // TODO: Set VT terminal when compiling on windows
    progress_bar.hide_cursor(std::cout);
    progress_bar.display(std::cout);
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
            progress_bar.tick();
            progress_bar.display(std::cout);
        }
        std::cout << std::endl;
        progress_bar.show_cursor(std::cout);
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