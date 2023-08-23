#pragma once
#include "commons.hpp"
class Ray
{
  private:
    vec3 rorigin, rdirection;

  public:
    Ray();
    Ray(const vec3 &p, const vec3 &d, bool normalized = false);
    // Returns a unit vector in the direction of this ray
    vec3 direction() const;
    // Returns the starting point of this ray
    vec3 origin() const;
    // Returns a point on this ray at a distance t from the origin
    vec3 at(double t) const;
};