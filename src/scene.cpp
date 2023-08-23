#include "scene.hpp"

Scene::Scene()
{
    // A test scene
    objects.push_back(std::make_shared<Sphere>(vec3(0, 0, -1), 0.5));
    objects.push_back(std::make_shared<Sphere>(vec3(0, -100.5, -1), 100));
}

colorf Scene::color_at(const Ray &ray, int row, int col, int image_width,
                       int image_height)
{
    colorf result;
    // Gets the point which is closest to the origin of the ray
    double min_intersection = INF;
    intersect_details min_intersect;
    for (const auto &obj : objects)
    {
        auto i = obj->intersection(intersect_params({ray, 0.001, INFINITY}));
        // If the current intersection is closer to the camera, choose it.
        if (i.occured && i.parametric < min_intersection)
        {
            min_intersect = i;
            min_intersection = i.parametric;
        }
    }
    if (min_intersection != INF)
    {
        vec3 unit = min_intersect.normal;
        return colorf(0.5 * (unit.x + 1), 0.5 * (unit.y + 1),
                      0.5 * (unit.z + 1));
    }
    // No intersections were found, display the sky colour
    double t = double(row) / (image_height - 1);
    return lerp(SKY_COLOR, LIGHT_SKY, t);
}