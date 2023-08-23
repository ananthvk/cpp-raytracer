#include "objects.hpp"

Sphere::Sphere() : center(vec3(0, 0, 0)), radius(0) {}
Sphere::Sphere(vec3 center, double radius) : center(center), radius(radius) {}

std::vector<double> Sphere::intersection(const Ray &ray) const
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