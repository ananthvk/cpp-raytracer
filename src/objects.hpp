#pragma once
#include "commons.hpp"
#include "ray.hpp"
#include <vector>

// A struct which stores some parameters for a ray intersecting with an object
struct Intersection
{
    // Point of intersection with ray.
    // If there are multiple points of intersection, the one with the least
    // distance from the origin of the ray is stored
    double parametric;
    // Point in cartesian system
    vec3 point;
    // The ray for which these values are calculated
    Ray ray;
    // The outward normal at the intersection point
    vec3 normal;
    // Local normal at the intersection point, normal at the side on which the
    // ray is present
    vec3 local_normal;
    // true if the intersection occured, otherwise false
    bool occured;
};

// parameters for the intersect function, ray, t_min, t_max
struct RayParams
{
    // The ray for which intersection has to be calculated
    Ray ray;
    // Minimum value of t which is valid
    double t_min;
    // Maximum value of t which is valid
    double t_max;
};

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

  public:
    Sphere();
    Sphere(vec3 center, double radius);
    Intersection intersect(const RayParams &params) const;
};
