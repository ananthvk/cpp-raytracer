#pragma once
#include "commons.hpp"
class Ray
{
  private:
    vec3 rpoint, rdirection;

  public:
    Ray() : rpoint(), rdirection() {}
    Ray(const vec3 &p, const vec3 &d, bool normalized = false) : rpoint(p)
    {
        if (normalized)
        {
            rdirection = d;
        }
        else
        {
            rdirection = linalg::normalize(d);
        }
    }
    // Returns a unit vector in the direction of this ray
    vec3 direction() const { return rdirection; }
    // Returns the starting point of this ray
    vec3 point() const { return rpoint; }
    // Returns a point on this ray at a distance t from the origin
    vec3 at(double t) const { return rpoint + (t * rdirection); }
};