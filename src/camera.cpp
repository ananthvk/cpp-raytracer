#include "camera.hpp"

MovableCamera::MovableCamera(int image_width, int image_height)
    : image_width(image_width), image_height(image_height)
{
    fov = radians(20);
    position = vec3(13, 2, 3);
    vec3 lookat = vec3(0, 0, 0);
    vec3 camera_up = vec3(0, 1, 0);

    defocus_angle = 0;//radians(0.6);
    focal_length = 10.0;

    // Calculated properties
    defocus_radius = focal_length * std::tan(defocus_angle / 2.0);
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
    // Translate the viewport, keeping the camera's position as origin.
    // The bug resulted in not shifting the origin of the viewport.
    auto pixel_sample = position + (up * vy) + (right * vx) + (direction * focal_length);
    auto ray_origin = (defocus_angle <= 0) ? position : get_defocused_origin();
    auto ray_direction = pixel_sample - ray_origin;

    return Ray(ray_origin, ray_direction);
}

// Get a random origin for a new ray on the plane of the actual origin of the camera
// This acts as thin lens approximation
vec3 MovableCamera::get_defocused_origin() const
{
    // auto rnd = random_in_unit_disk();
    // return defocus_radius * ((rnd[0] * right) + (rnd[1] * up));
    auto p = random_in_unit_disk();
    return position + (p[0] * up * defocus_radius) + (p[1] * right * defocus_radius);
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
    os << "Defocus angle:" << defocus_angle << std::endl;
    os << "Defocus radius:" << defocus_radius << std::endl;
    os << "Defocus u:" << defocus_radius * right << std::endl;
    os << "Defocus v:" << defocus_radius * up << std::endl;
    os << "******************" << std::endl;
}