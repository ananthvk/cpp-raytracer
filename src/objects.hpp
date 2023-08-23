#pragma once
#include "commons.hpp"
#include "ray.hpp"
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
    Sphere();
    Sphere(vec3 center, double radius);
    std::vector<double> intersection(const Ray &ray) const;
};
