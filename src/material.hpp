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

struct MaterialInteraction
{
    // true if this interaction produces other rays which have to be processed
    bool additional_rays;
    // Additional rays produced due to this interaction
    Ray ray;
    // Color due to this material
    color attenuation;
};

// An abstract class for any material
class Material
{
  public:
    virtual MaterialInteraction interact(const RayParams &params,
                                         const Intersection &intersect) const = 0;

    virtual ~Material() {}
};

class LambertianDiffuse : public Material
{
  public:
    // By default the color of the material is gray, (0.5, 0.5, 0.5)
    LambertianDiffuse();

    LambertianDiffuse(const color &albedo);

    MaterialInteraction interact(const RayParams &params,
                                 const Intersection &intersect) const override;

  private:
    // Albedo or color of this material
    color albedo;
};

class NormalShader : public Material
{
  public:
    MaterialInteraction interact(const RayParams &params,
                                 const Intersection &intersect) const override
    {

        // Shade the normals
        MaterialInteraction interaction;
        auto v = 0.5 * (intersect.local_normal + vec3(1, 1, 1));
        interaction.additional_rays = false;
        interaction.attenuation = v;
        return interaction;
    }
};

class Metal : public Material
{
  public:
    // By default the color of the material is gray
    Metal();

    Metal(const color &albedo, double fuzziness = 0.0);

    MaterialInteraction interact(const RayParams &params,
                                 const Intersection &intersect) const override;

  private:
    // Albedo or color of this material
    color albedo;
    double fuzziness;
};

class Glass : public Material
{
  public:
    Glass();
    Glass(const color &albedo, double r_index = 1.5);
    MaterialInteraction interact(const RayParams &params,
                                 const Intersection &intersect) const override;

  private:
    // Albedo or color of this material
    color albedo;
    double r_index;
};