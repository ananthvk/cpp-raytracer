#include "camera.hpp"

MovableCamera::MovableCamera(int image_width, int image_height)
    : image_width(image_width), image_height(image_height)
{
    // position = vec3(0.0, 0.0, 0.0);       // The position of the camera
    // vec3 lookat = vec3(0.0, 0.0, -1.0);   // The point the camera is looking at
    // vec3 camera_up = vec3(0.0, 1.0, 0.0); // The up direction relative to the camera
    fov = (PI / 180.0) * 90;
    position = vec3(-2, 2, 1);
    vec3 lookat = vec3(0, 0, -1);
    vec3 camera_up = vec3(0, 1, 0);


    focal_length = 10;
    // linalg::length(lookat - position); // Distance between the camera and the lookat
    // Use the Gram-Schimdt process to find the orthonormal basis
    // https://en.wikipedia.org/wiki/Gram%E2%80%93Schmidt_process

    // Define the basis for calculating the rays
    direction = linalg::normalize(lookat - position);
    // Use left-handed coordinate system, camera points towards positive z
    right = linalg::normalize(linalg::cross(direction, camera_up));
    up = linalg::normalize(linalg::cross(right, direction));

    aspect_ratio = static_cast<double>(image_width) / image_height;
    viewport_height = 2.0 * std::tan(fov / 2.0) * focal_length;
    viewport_width = aspect_ratio * viewport_height;
    delta_x = viewport_width / image_width;
    delta_y = viewport_height / image_height;
}

// Returns a ray which passes through a pixel at (row, col)
// Note: pixels start from (0,0), which is the top left corner
Ray MovableCamera::get_ray(int row, int col, bool sample) const
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
    if (sample)
    {
        vx += (uniform() - 0.5) * delta_x;
        vy += (uniform() - 0.5) * delta_y;
    }
    vec3 vpoint = (up * vy) + (right * vx) + (direction * focal_length);
    std::cout << "PIXEL IMPL" << vpoint << std::endl;
    std::cout << "*Component along direction:" << direction * focal_length << std::endl;
    std::cout << "*Component along u (horizontal):" << right * vx << std::endl;
    std::cout << "*Component along v (vertical):" << up * vy << std::endl;
    std::cout << "*Sum without center: " << direction * focal_length + right * vx + up * vy
              << std::endl;
    std::cout << "*Sum with center: " << position + direction * focal_length + right * vx + up * vy
              << std::endl;
    return Ray(position, vpoint - position);
}

void MovableCamera::debug_info(std::ostream &os) const
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
    os << "Delta x:" << delta_x << std::endl;
    os << "Delta y:" << delta_y << std::endl;
    os << "******************" << std::endl;
}