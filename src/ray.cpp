#include "ray.hpp"

Ray::Ray(const vec3 &p, const vec3 &d, bool normalized) : rorigin(p)
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

Ray::Ray() : rorigin(), rdirection() {}

vec3 Ray::direction() const { return rdirection; }

vec3 Ray::origin() const { return rorigin; }

vec3 Ray::at(double t) const { return rorigin + (t * rdirection); }