#include "scene.hpp"

Scene::Scene()
{
    // A sample render scene
    materials.push_back(new LambertianDiffuse(color(0.5, 0.5, 0.5)));
    materials.push_back(new Glass(WHITE, 1.5));
    materials.push_back(new LambertianDiffuse(color(0.4, 0.2, 0.1)));
    materials.push_back(new Metal(color(0.7, 0.6, 0.5), 0.0));

    objects.push_back(new Sphere(vec3(0, -1000, 0), 1000, 0));
    objects.push_back(new Sphere(vec3(0, 1, 0), 1.0, 1));
    objects.push_back(new Sphere(vec3(-4, 1, 0), 1.0, 2));
    objects.push_back(new Sphere(vec3(4, 1, 0), 1.0, 3));
}

color Scene::color_at(const Ray &ray, int recursion_limit)
{
    if (recursion_limit == 0)
    {
        // The function has reached recursion limit, so no more light can be
        // gathered, so return black.
        return color(0, 0, 0);
    }
    // 0.001 is used to prevent intersection of the ray with the same surface
    // from which it is cast, to prevent shadow acne
    auto params = RayParams({ray, 0.001, INFINITY});
    // Find the closest intersection of this ray in this given scene
    Intersection intersect = closest_intersect(params);
    if (intersect.occured)
    {
        // Perform material-ray interactions, such as reflection, refraction, etc
        auto interaction = materials[intersect.material_id]->interact(params, intersect);
        if (interaction.additional_rays)
        {
            return linalg::cmul(interaction.attenuation,
                                color_at(interaction.ray, recursion_limit - 1));
        }
        return interaction.attenuation;
    }
    // The ray does not intersect with any object, so return the sky color
    double t = 0.5 * (ray.direction().y + 1.0);
    return lerp(WHITE, SKY_COLOR_2, t);
}

Intersection Scene::closest_intersect(const RayParams &params)
{
    double intersect_distance = INF;
    Intersection closest;
    closest.occured = false;
    for (const auto &obj : objects)
    {
        auto i = obj->intersect(params);
        // If this intersection is closer to the ray's origin, choose it as the closest intersection
        if (i.occured && i.parametric < intersect_distance)
        {
            intersect_distance = i.parametric;
            closest = i;
        }
    }
    return closest;
}

Scene::~Scene()
{
    for (size_t i = 0; i < materials.size(); ++i)
    {
        delete materials[i];
    }
    for (size_t i = 0; i < objects.size(); ++i)
    {
        delete objects[i];
    }
}
