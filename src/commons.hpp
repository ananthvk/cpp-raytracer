#pragma once
#include "linalg.h"
#include <limits>
#include <random>
constexpr double PI = 3.141592653589793238463;

// Function to perform linear interpolation
inline float lerp(float s, float e, float t) { return (1 - t) * s + t * e; }

using vec3 = linalg::vec<double, 3>;
const double INF = std::numeric_limits<double>::infinity();

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