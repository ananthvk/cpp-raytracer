#include "scene.hpp"

Scene::Scene()
{
    // A test scene
    objects.push_back(std::make_shared<Sphere>(vec3(0, 0, -1), 0.5));
    objects.push_back(std::make_shared<Sphere>(vec3(0, -100.5, -1), 100));
}

color Scene::color_at(const Ray &ray, int row, int col, int image_width,
                      int image_height, int recursion_limit)
{
    if (recursion_limit == 0)
    {
        // The function has reached recursion limit, no more light can be gathered
        // so return black
        return color(0, 0, 0);
    }
    color result;
    Intersection intersect = closest_intersect(RayParams({ray, 0, INFINITY}));
    if (intersect.occured)
    {
        auto normal = intersect.normal;
        if (linalg::dot(normal, ray.direction()) >= 0)
        {
            normal = -normal;
        }
        auto v = 0.5 * (normal + vec3(1, 1, 1));
        return color(v.x, v.y, v.z);
    }
    else
    {
        // No intersections were found, display the sky colour
        double t = 0.5 * (ray.direction().y + 1.0);
        return lerp(WHITE, SKY_COLOR_2, t);
    }
}

Intersection Scene::closest_intersect(const RayParams &params)
{
    double intersect_distance = INF;
    Intersection closest;
    closest.occured = false;
    for (const auto &obj : objects)
    {
        auto i = obj->intersect(params);
        // If this intersection is closer to the ray's origin, choose it
        if (i.occured && i.parametric < intersect_distance)
        {
            intersect_distance = i.parametric;
            closest = i;
        }
    }
    return closest;
}