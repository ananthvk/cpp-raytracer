#pragma once
#include "commons.hpp"
#include <iostream>
#include <ostream>
using namespace linalg::ostream_overloads;

class Camera
{
  public:
    virtual Ray get_ray(int row, int col, bool sample = false) const = 0;
    virtual void debug_info(std::ostream &os) const = 0;

    virtual ~Camera() {}
};

class MovableCamera : public Camera
{
  private:
    // Note unless specified, all angle values are in radians
    // A vector which represents the alignment of the camera
    vec3 up;
    // A vector which points to the right of the camera
    vec3 right;
    // The direction the camera is looking at
    vec3 direction;
    // Position of the camera
    vec3 position;
    // Distance between the camera and the viewport screen
    double focal_length;
    // FOV angle
    double fov;
    // Width of the image (in pixels)
    int image_width;
    // Height of the image (in pixels)
    int image_height;
    // Aspect ratio is width / height
    double aspect_ratio;
    // Width of the virtual viewport (in metres)
    double viewport_width;
    // Height of the virtual viewport (in metres)
    double viewport_height;
    // It is the horizontal spacing between two adjacent pixels in the viewport
    double delta_x;
    // It is the vertical spacing between two adjacent pixels in the viewport
    double delta_y;
    // The angle through which the rays are spread out from the origin of the camera
    double defocus_angle;
    // The radius of disk from which rays are cast to the screen
    double defocus_radius;

    // Returns a random origin for a new ray on the defocus disk
    vec3 get_defocused_origin() const;

  public:
    MovableCamera();
    // Returns a ray which passes through a pixel at (row, col)
    // Note: pixels start from (0,0), which is the top left corner
    Ray get_ray(int row, int col, bool sample = false) const override;
    void debug_info(std::ostream &os) const override;
};