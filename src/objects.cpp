#include "objects.hpp"

Sphere::Sphere() : center(vec3(0, 0, 0)), radius(0) {}
Sphere::Sphere(vec3 center, double radius) : center(center), radius(radius) {}

intersect_details Sphere::intersection(const intersect_params &params) const
{
    intersect_details details;
    details.occured = false;
    auto ray = params.ray;
    // Solving sphere-ray quadratic equation
    vec3 AC = ray.origin() - center;
    double a = linalg::dot(ray.direction(), ray.direction());
    double b = 2.0 * linalg::dot(ray.direction(), AC);
    double c = linalg::dot(AC, AC) - radius * radius;
    double discriminant = b * b - 4 * a * c;
    double sqd = std::sqrt(discriminant);
    if (discriminant >= 0)
    {
        // Return the intersection point of the sphere with the ray
        double root = (-b - sqd) / (2.0 * a);
        if (params.t_min <= root && root <= params.t_max)
        {
            details.occured = true;
            details.parametric = root;
            details.point = ray.at(root);
            details.normal = (details.point - center) / radius;
        }
        else
        {
            // Check if the other root lies in range
            root = (-b + sqd) / (2.0 * a);
            if (params.t_min <= root && root <= params.t_max)
            {
                details.occured = true;
                details.parametric = root;
                details.point = ray.at(root);
                details.normal = (details.point - center) / radius;
            }
        }
    }
    return details;
}