#pragma once
#include "commons.hpp"
constexpr int IMAGE_WIDTH = 400;
constexpr int IMAGE_HEIGHT = IMAGE_WIDTH * (9.0 / 16.0);
constexpr int PROGRESSBAR_WIDTH = 40;
constexpr int SAMPLES_PER_PIXEL = 100; // NOTE: MUST BE NON-ZERO AND POSITIVE
constexpr int RECURSION_LIMIT = 50;
constexpr double CAMERA_FOV = radians(20);
constexpr vec3 CAMERA_POSITION = vec3(13, 2, 3);
constexpr vec3 CAMERA_LOOKAT = vec3(0, 0, 0);
constexpr vec3 CAMERA_UP = vec3(0, 1, 0);
constexpr double CAMERA_DEFOCUS_ANGLE = radians(0);
constexpr double CAMERA_FOCAL_LENGTH = 10.0;