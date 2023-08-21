#pragma once
#include "commons.hpp"

// A struct to represent colors
struct colorf
{
    double r;
    double g;
    double b;
    colorf() : r(0), g(0), b(0) {}
    colorf(double r, double g, double b) : r(r), g(g), b(b) {}
    static colorf from_rgb(int r, int g, int b)
    {
        return colorf((double)r / 255, (double)g / 255, (double)b / 255);
    }
};

// Performs linear interpolation between two colors
colorf lerp(colorf s, colorf e, float t)
{
    return colorf(lerp(s.r, e.r, t), lerp(s.g, e.g, t), lerp(s.b, e.b, t));
}

// Some commonly used colors
const colorf SKY_COLOR = colorf::from_rgb(135, 206, 235);
const colorf WHITE = colorf::from_rgb(255, 255, 255);
const colorf LIGHT_SKY = colorf::from_rgb(188, 227, 244);
const colorf GREEN = colorf(0, 1, 0);
const colorf BLUE = colorf(0, 0, 1);
