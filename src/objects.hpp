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
#pragma once
#include "commons.hpp"
#include <vector>

// A class to represent any object which can be rendered on the screen
class Object
{
  public:
    virtual Intersection intersect(const RayParams &params) const = 0;

    virtual ~Object() {}
};

// A class for a sphere object, has center, radius and material as parameters
class Sphere : public Object
{
  private:
    vec3 center;
    double radius;
    int material_id;

  public:
    /// @brief  Default constructor, the sphere is at (0, 0, 0) with radius 0
    Sphere();

    /// @brief Create a new sphere given the material
    /// @param center Center of the sphere
    /// @param radius Radius of the sphere
    /// @param material_id index of the material of the sphere in the materials array/vector
    Sphere(vec3 center, double radius, int material_id);

    /// @brief Finds the intersection between this sphere and the given ray
    /// @param RayParams Ray parameters, such as the ray, minimum allowed t and max allowed t
    Intersection intersect(const RayParams &params) const;

    /// @brief Sets the material of the sphere from the materials array/vector
    void set_material_id(int id);
};
