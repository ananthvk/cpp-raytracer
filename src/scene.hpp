#pragma once
#include "colors.hpp"
#include "commons.hpp"
#include "objects.hpp"
#include "ray.hpp"
#include <memory>

class Scene
{
  private:
    std::vector<std::shared_ptr<Object>> objects;

  public:
    Scene();
    // Returns the color of the ray in this scene
    colorf color_at(const Ray &ray, int row, int col, int image_width,
                    int image_height);
};