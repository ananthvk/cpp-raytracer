#include "scene.hpp"

Scene::Scene()
{
    objects.push_back(std::make_shared<Sphere>(vec3(0, 0, -1), 0.5));
}

colorf Scene::color_at(const Ray &ray, int row, int col, int image_width,
                       int image_height)
{
    colorf result;
    for (const auto &obj : objects)
    {
        if (!(obj->intersection(ray).empty()))
        {
            return BLUE;
        }
    }
    double t = double(row) / (image_height - 1);
    return lerp(SKY_COLOR, LIGHT_SKY, t);
}