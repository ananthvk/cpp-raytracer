#include "scene.hpp"

Scene::Scene()
{
    // A test scene
    objects.push_back(std::make_shared<Sphere>(vec3(0, 0, -1), 0.5));
    objects.push_back(std::make_shared<Sphere>(vec3(0, -100.5, -1), 100));
}

color Scene::color_at(const Ray &ray, int recursion_limit)
{
    if (recursion_limit == 0)
    {
        // The function has reached recursion limit, no more light can be
        // gathered so return black
        return color(0, 0, 0);
    }
    color result;
    // 0.001 is used to intersection of the ray with the same surface
    // from which it is cast
    Intersection intersect =
        closest_intersect(RayParams({ray, 0.001, INFINITY}));
    if (intersect.occured)
    {
        // Shade the normals
        // auto v = 0.5 * (intersect.local_normal + vec3(1, 1, 1));
        // return color(v.x, v.y, v.z);

        // Diffuse materials
        // In these materials, rays which are incident on the surface are
        // randomly reflected in all directions.
        auto random_direction = random_in_unit_sphere();
        // If the unit vector and the ray are not on the same side, flip the
        // vector
        if (linalg::dot(intersect.local_normal, random_direction) < 0.0)
        {
            random_direction = -random_direction;
        }
        return 0.5 * color_at(Ray(intersect.point, random_direction),
                              recursion_limit - 1);
    }
    else
    {
        // The ray does not intersect with any object, so return the sky color
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