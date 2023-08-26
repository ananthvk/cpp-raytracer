#pragma once
#include "linalg.h"
#include <limits>
#include <random>
constexpr double PI = 3.141592653589793238463;
constexpr double ZERO_EPSILON = 0.0;

// Function to perform linear interpolation
inline float lerp(float s, float e, float t) { return (1 - t) * s + t * e; }

using vec3 = linalg::vec<double, 3>;
const double INF = std::numeric_limits<double>::infinity();

class Ray
{
  private:
    vec3 rorigin, rdirection;

  public:
    Ray() : rorigin(), rdirection() {}

    Ray(const vec3 &p, const vec3 &d, bool normalized = false) : rorigin(p)
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
    vec3 origin() const { return rorigin; }

    // Returns a point on this ray at a distance t from the origin of the ray
    vec3 at(double t) const { return rorigin + (t * rdirection); }
};

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
    // id(index) of the material at the intersection point
    int material_id;
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

// Gets a random number between 0 and 1
inline double uniform()
{
    std::random_device rd;
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator(rd());
    return distribution(generator);
}

inline double uniform(double min, double max)
{
    static std::uniform_real_distribution<double> distribution(min, max);
    static std::mt19937 generator;
    return distribution(generator);
}

// This function returns a random unit vector inside a sphere
inline vec3 random_in_unit_sphere()
{
    while (1)
    {
        vec3 v(uniform(-1, 1), uniform(-1, 1), uniform(-1, 1));
        if (linalg::length2(v) < 1)
            return linalg::normalize(v);
    }
}

// Returns true if the vector is a zero vector
inline bool is_zero_vector(const vec3 &v)
{
    return fabs(v.x) < ZERO_EPSILON && fabs(v.y) < ZERO_EPSILON && fabs(v.z) < ZERO_EPSILON;
}

// Returns the ray after reflection
inline vec3 reflect(const vec3 &v, const vec3 &n) { return v - 2 * linalg::dot(v, n) * n; }
