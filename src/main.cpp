#include "camera.hpp"
#include "colors.hpp"
#include "image.hpp"
#include "progressbar.hpp"
#include "scene.hpp"
#include <iostream>

const int image_width = 400;
const int image_height = 225;
const int PROGRESSBAR_WIDTH = 40;
const int SAMPLES_PER_PIXEL = 1; // NOTE: MUST BE NON-ZERO AND POSITIVE
const int RECURSION_LIMIT = 50;

int main()
{
    int k = 0;
    int max_val = image_height;
    ReferenceCamera cam;
    MovableCamera cam2(image_width, image_height);
    cam2.debug_info(std::cout);
    Scene scene;
    cam.debug_info(std::cout);
    // TODO: Set VT terminal when compiling on windows
    progressbar_hide_cursor();
    progressbar_display(std::cout, k, max_val, PROGRESSBAR_WIDTH);
    try
    {
        image img(image_height, image_row(image_width, color()));
        for (int i = 0; i < image_height; ++i)
        {
            for (int j = 0; j < image_width; ++j)
            {
                color pixel_color(0, 0, 0);
                for (int sample = 0; sample < SAMPLES_PER_PIXEL; ++sample)
                {
                    auto ray = cam.get_ray(i, j, SAMPLES_PER_PIXEL > 1);
                    auto ray2 = cam2.get_ray(i, j, SAMPLES_PER_PIXEL > 1);
                    if ((!almost_equal(ray.origin(), ray2.origin())) ||
                        (!almost_equal(ray.direction(), ray2.direction())))
                    {
                        std::cout << "i = " << i << " j = " << j << std::endl;
                        std::cout << "Reference:" << std::endl;
                        std::cout << "Origin:" << ray.origin() << " Direction:" << ray.direction()
                                  << std::endl;
                        std::cout << "\nImpl:" << std::endl;
                        std::cout << "Origin:" << ray2.origin() << " Direction:" << ray2.direction()
                                  << std::endl;
                        exit(2);
                    }
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