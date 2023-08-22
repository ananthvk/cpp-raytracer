#include "camera.hpp"

RegularCamera::RegularCamera(int image_width, int image_height)
    : image_width(image_width), image_height(image_height)
{
    up = vec3(0.0, 1.0, 0.0);
    right = vec3(1.0, 0.0, 0.0);
    // The camera faces the negative z axis
    direction = vec3(0.0, 0.0, -1.0);
    // The camera is at the origin
    position = vec3(0.0, 0.0, 0.0);
    // focal length of 1m
    focal_length = 1.0;
    // 90 degrees FOV
    fov = PI / 2.0;
    // 16:9 aspect ratio
    aspect_ratio = static_cast<double>(image_width) / image_height;
    // tan (theta/2) = h/(focal length).
    viewport_height = 2.0 * std::tan(fov / 2.0) * focal_length;
    viewport_width = aspect_ratio * viewport_height;
    delta_x = viewport_width / image_width;
    delta_y = viewport_height / image_height;
}

// Returns a ray which passes through a pixel at (row, col)
// Note: pixels start from (0,0), which is the top left corner
Ray RegularCamera::get_ray(int row, int col)
{
    // Find the other point on this ray, one end point is the position of
    // the camera.
    // In PCC (Pixel coordinate system), the center is represented as
    // image_width/2, image_height/2
    double x0 = std::max(image_width / 2.0, 1.0);
    double y0 = std::max(image_height / 2.0, 1.0);
    // x and y represent the position of the pixel in cartesian system on
    // the viewport (but as pixels)
    double x = col - x0;
    double y = y0 - row;
    // Convert the pixel values to viewport system
    double vx = x * delta_x;
    double vy = y * delta_y;
    vec3 vpoint = up * vy + right * vx + direction * focal_length;
    return Ray(position, vpoint - position);
}

void RegularCamera::debug_info(std::ostream &os)
{
    os << "Camera debug info" << std::endl;
    os << "******************" << std::endl;
    os << "Up: " << up << std::endl;
    os << "Right: " << right << std::endl;
    os << "Direction: " << direction << std::endl;
    os << "Position: " << position << std::endl;
    os << "Focal length: " << focal_length << std::endl;
    os << "FOV: " << fov << std::endl;
    os << "Image width: " << image_width << std::endl;
    os << "Image height: " << image_height << std::endl;
    os << "Aspect ratio: " << aspect_ratio << std::endl;
    os << "Viewport width: " << viewport_width << std::endl;
    os << "Viewport height: " << viewport_height << std::endl;
    os << "******************" << std::endl;
}