#pragma once
#include "linalg.h"
constexpr double PI = 3.141592653589793238463;

// Function to perform linear interpolation
float lerp(float s, float e, float t) { return (1 - t) * s + t * e; }

using vec3 = linalg::vec<double, 3>;