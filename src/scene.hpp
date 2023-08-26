#pragma once
#include "colors.hpp"
#include "commons.hpp"
#include "material.hpp"
#include "objects.hpp"
#include <memory>

class Scene
{
  private:
    std::vector<std::shared_ptr<Object>> objects;
    std::vector<std::shared_ptr<Material>> materials;

  public:
    Scene();
    // Returns the color of the ray when it is incident on this scene
    color color_at(const Ray &ray, int recursion_limit);
    // Finds the closest or first intersection of a ray with all object
    // in this scene.
    Intersection closest_intersect(const RayParams &params);
};