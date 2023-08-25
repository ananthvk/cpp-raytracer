#pragma once
#include "commons.hpp"

// Use vec3 instead of creating a custom struct to simplify the implementation
// and to avoid defining custom operator overloads
using color = vec3;
static color color_from_rgb(int r, int g, int b)
{
    return color((double)r / 255, (double)g / 255, (double)b / 255);
}
// Performs linear interpolation between two colors
inline color lerp(color s, color e, float t)
{
    return color(lerp(s.x, e.x, t), lerp(s.y, e.y, t), lerp(s.z, e.z, t));
}

// Some commonly used colors
const color SKY_COLOR = color_from_rgb(135, 206, 235);
const color SKY_COLOR_2 = color(0.5, 0.7, 1.0);
const color WHITE = color_from_rgb(255, 255, 255);
const color LIGHT_SKY = color_from_rgb(188, 227, 244);
const color RED = color(1, 0, 0);
const color GREEN = color(0, 1, 0);
const color BLUE = color(0, 0, 1);
const color BLACK = color(0, 0, 0);

inline color gamma_correction(color color, int power)
{
    color.x = std::pow(color.x, 1.0 / power);
    color.y = std::pow(color.y, 1.0 / power);
    color.z = std::pow(color.z, 1.0 / power);
    return color;
}