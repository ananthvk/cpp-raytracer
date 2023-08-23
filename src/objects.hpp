#pragma once
#include "commons.hpp"
#include "ray.hpp"
#include <vector>

// A struct which stores some parameters for a ray intersecting with an object
struct intersect_details
{
    // Point of intersection with ray.
    // If there are multiple points of intersection, the one with the least
    // distance from the origin of the ray is stored
    double parametric;
    // Point in cartesian system
    vec3 point;
    // The ray for which these values are calculated
    Ray ray;
    // Always store the outward normal at the point
    vec3 normal;
    // true if the intersection occured, otherwise false
    bool occured;
};

// parameters for the intersect function, ray, t_min, t_max
struct intersect_params
{
    // Check if this ray intersects with any object.
    Ray ray;
    // Minimum value of t which is valid
    double t_min;
    // Maximum value of t which is valid
    double t_max;
};

class Object
{
  public:
    virtual intersect_details
    intersection(const intersect_params &params) const = 0;
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
    intersect_details intersection(const intersect_params &params) const;
};
