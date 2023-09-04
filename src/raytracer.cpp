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
#include "raytracer.hpp"
#include "image.hpp"
#include "progressbar.hpp"
#include <iostream>

Renderer::Renderer(const Config &config) : config(config) {}

void Renderer::set_config(const Config cfg) { config = cfg; }

Config Renderer::get_config() const { return config; }

void Renderer::render(const Camera &cam, const Scene &scene) const
{
    ProgressBar progress_bar(config.image_height, config.progressbar_width, true);
    progress_bar.hide_cursor(std::cout);
    progress_bar.display(std::cout);
    try
    {
        image img(config.image_height, image_row(config.image_width, color()));
        // For each pixel in the image, generate a ray from the camera,
        // then get the color of the ray from the scene.
        // Perform this operation a number of times to sample average the color value for a
        // particular pixel
        for (int i = 0; i < config.image_height; ++i)
        {
            for (int j = 0; j < config.image_width; ++j)
            {
                color pixel_color(0, 0, 0);
                for (int sample = 0; sample < config.samples_per_pixel; ++sample)
                {
                    auto ray = cam.get_ray(i, j, config.samples_per_pixel > 1);
                    pixel_color += scene.color_at(ray, config.recursion_limit);
                }
                pixel_color /= config.samples_per_pixel;
                // Apply gamma correction, so that the image gets saved accurately
                // Apply gamma 2
                pixel_color = gamma_correction(pixel_color, config.gamma);
                img[i][j] = pixel_color;
            }
            progress_bar.tick();
            progress_bar.display(std::cout);
        }
        std::cout << std::endl;
        progress_bar.show_cursor(std::cout);
        std::cout << "Writing to disk....." << std::endl;
        write_to_file(config.filename, img);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: Error while rendering!" << std::endl;
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}
