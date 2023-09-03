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
#include "colors.hpp"
#include "commons.hpp"
#include "material.hpp"
#include "objects.hpp"

class Scene
{
  private:
    std::vector<Object *> objects;
    std::vector<Material *> materials;

  public:
    Scene();

    /// @param ray Input ray
    /// @param recursion_limit Number of times this ray can bounce, after every bounce it is
    /// decreased by one
    /// @return The color of the ray when it passes through this scene
    color color_at(const Ray &ray, int recursion_limit);

    /// @param params Ray parameters
    /// @return The intersection which is closest to the ray's origin
    Intersection closest_intersect(const RayParams &params);
    ~Scene();
};