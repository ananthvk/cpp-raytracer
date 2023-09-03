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
        // For each pixel in the image, generate a ray from the camera,
        // then get the color of the ray from the scene.
        // Perform this operation a number of times to sample average the color value for a
        // particular pixel
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
                // Apply gamma correction, so that the image gets saved accurately
                // Apply gamma 2
                pixel_color = gamma_correction(pixel_color, GAMMA);
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