#pragma once

// Function to perform linear interpolation
float lerp(float s, float e, float t) { return (1 - t) * s + t * e; }