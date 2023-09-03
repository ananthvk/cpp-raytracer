// MIT License
// 
// Copyright (c) 2023 Ananthanarayanan Venkitakrishnan (https://github.com/ananthvk)
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#include "objects.hpp"

Sphere::Sphere() : center(vec3(0, 0, 0)), radius(0), material_id(0) {}

Sphere::Sphere(vec3 center, double radius, int material_id)
    : center(center), radius(radius), material_id(material_id)
{
}

Intersection Sphere::intersect(const RayParams &params) const
{
    Intersection details;
    // No intersections are expected, so by default occured is set to false
    details.occured = false;
    auto ray = params.ray;
    // Solving sphere-ray quadratic equation
    vec3 AC = ray.origin() - center;
    double a = linalg::dot(ray.direction(), ray.direction());
    double b = 2.0 * linalg::dot(ray.direction(), AC);
    double c = linalg::dot(AC, AC) - radius * radius;
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
    {
        // There is no solution, the ray does not intersect the sphere
        return details;
    }
    double sqd = std::sqrt(discriminant);
    double root = (-b - sqd) / (2.0 * a);
    // Check if the root does not lie within the given range
    if (root < params.t_min || root > params.t_max)
    {
        root = (-b + sqd) / (2.0 * a);
        // Check if the other root does not lie in the range
        if (root < params.t_min || root > params.t_max)
        {
            // Both roots do not lie in range, there is no solution
            return details;
        }
    }
    details.occured = true;
    details.parametric = root;
    details.point = ray.at(root);
    // Find the outward normal or the normal which always points out of the sphere
    details.o_normal = (details.point - center) / radius;
    details.material_id = material_id;
    details.ray = params.ray;
    // Find the local normal, or the normal on the side of the ray
    if (linalg::dot(details.o_normal, ray.direction()) > 0.0)
    {
        // The ray is inside the sphere
        details.front = false;
        details.local_normal = -details.o_normal;
    }
    else
    {
        // The ray is outside the sphere
        details.front = true;
        details.local_normal = details.o_normal;
    }
    return details;
}

void Sphere::set_material_id(int id) { material_id = id; }