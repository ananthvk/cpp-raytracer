#include "scene.hpp"

Scene::Scene()
{
    // A test scene
    objects.push_back(std::make_shared<Sphere>(vec3(0, 0, -1), 0.5));
    objects.push_back(std::make_shared<Sphere>(vec3(0, -100.5, -1), 100));
}

colorf Scene::color_at(const Ray &ray, int row, int col, int image_width,
                       int image_height, int recursion_limit)
{
    if (recursion_limit == 0)
    {
        vec3 unit_direction = ray.direction();
        auto a = 0.5 * (unit_direction.y + 1.0);
        return (1.0 - a) * colorf(1.0, 1.0, 1.0) + a * colorf(0.5, 0.7, 1.0);
    }
    colorf result;
    // Gets the point which is closest to the origin of the ray
    double min_intersection = INF;
    intersect_details min_intersect;
    for (const auto &obj : objects)
    {
        auto i = obj->intersection(intersect_params({ray, 0, INFINITY}));
        // If the current intersection is closer to the camera, choose it.
        if (i.occured && i.parametric < min_intersection)
        {
            min_intersect = i;
            min_intersection = i.parametric;
        }
    }
    if (min_intersection != INF)
    {
        auto normal = min_intersect.normal;
        if (linalg::dot(normal, ray.direction()) >= 0)
        {
            // The ray and the normal are passing out on the same side (which
            // means that the ray is entering from inside the sphere)
            normal = -normal;
        }
        auto v = 0.5 * (normal + vec3(1, 1, 1));
        return colorf(v.x, v.y, v.z);
    }
    // No intersections were found, display the sky colour
    double t = 0.5 * (ray.direction().y + 1.0);
    return lerp(WHITE, SKY_COLOR_2, t);
}