#pragma once
#include <eigen3/Eigen/StdVector>
// Function to perform linear interpolation
float lerp(float s, float e, float t) { return (1 - t) * s + t * e; }

using vec3 = Eigen::Vector3d;