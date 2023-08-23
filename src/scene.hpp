#pragma once
#include "colors.hpp"
#include "commons.hpp"
#include "ray.hpp"
#include <memory>
#include <vector>

class Object
{
  public:
    virtual std::vector<double> intersection(const Ray &ray) const = 0;
    virtual ~Object() {}
};

class Sphere : public Object
{
  private:
    vec3 center;
    double radius;

  public:
    Sphere() : center(vec3(0, 0, 0)), radius(0) {}
    Sphere(vec3 center, double radius) : center(center), radius(radius) {}
    std::vector<double> intersection(const Ray &ray) const
    {
        vec3 AC = ray.origin() - center;
        double a = linalg::dot(ray.direction(), ray.direction());
        double b = 2.0 * linalg::dot(ray.direction(), AC);
        double c = linalg::dot(AC, AC) - radius * radius;
        double discriminant = b * b - 4 * a * c;
        if (discriminant < 0)
        {
            return std::vector<double>();
        }
        else
        {
            // TODO: Temporary
            return std::vector<double>(1, 0);
        }
    }
};

class Scene
{
  private:
    std::vector<std::shared_ptr<Object>> objects;

  public:
    Scene()
    {
        objects.push_back(std::make_shared<Sphere>(vec3(0, 0, -1), 0.5));
    }
    // Returns the color of the ray in this scene
    colorf color_at(const Ray &ray, int row, int col, int image_width,
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
};