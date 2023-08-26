#pragma once
#include "commons.hpp"
#include <vector>

class Object
{
  public:
    virtual Intersection intersect(const RayParams &params) const = 0;

    virtual ~Object() {}
};

class Sphere : public Object
{
  private:
    vec3 center;
    double radius;
    int material_id;

  public:
    Sphere();
    Sphere(vec3 center, double radius, int material_id);
    Intersection intersect(const RayParams &params) const;
    void set_material_id(int id);
};
