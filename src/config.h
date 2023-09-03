// MIT License
// 
// Copyright (c) 2023 Ananthanarayanan Venkitakrishnan (https://github.com/ananthvk)
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// Some configuration options such as image width, height, samples per pixel, etc
#pragma once
#include "commons.hpp"
constexpr int GAMMA = 2;
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