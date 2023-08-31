// The code below has been taken from the book to help debug or find bugs
#include "camera.hpp"

class ReferenceCamera : public Camera
{
  public:
    double aspect_ratio = 16.0 / 9.0; // Ratio of image width over height
    int image_width = 400;            // Rendered image width in pixel count
    int samples_per_pixel = 100;      // Count of random samples for each pixel
    int max_depth = 50;               // Maximum number of ray bounces into scene

    double vfov = 90; // Vertical view angle (field of view)
    vec3 lookfrom = vec3(-2, 2, 1);
    vec3 lookat = vec3(0, 0, -1);
    vec3 vup = vec3(0, 1, 0);

    double focus_dist = 10; // Distance from camera lookfrom point to plane of perfect focus

    ReferenceCamera() { initialize(); }

    Ray get_ray(int j, int i, bool sample = false) const override
    {
        // Get a randomly-sampled camera ray for the pixel at location i,j, originating from
        // the camera defocus disk.

        auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
        auto pixel_sample = pixel_center;
        if (sample)
        {
            pixel_sample += pixel_sample_square();
        }
        auto ray_origin = center;
        auto ray_direction = pixel_sample - ray_origin;

        return Ray(ray_origin, ray_direction);
    }

    void debug_info(std::ostream &os) const override
    {
        os << "Reference book camera!\n" << std::endl;
    }

  private:
    int image_height;    // Rendered image height
    vec3 center;         // Camera center
    vec3 pixel00_loc;    // Location of pixel 0, 0
    vec3 pixel_delta_u;  // Offset to pixel to the right
    vec3 pixel_delta_v;  // Offset to pixel below
    vec3 u, v, w;        // Camera frame basis vectors
    vec3 defocus_disk_u; // Defocus disk horizontal radius
    vec3 defocus_disk_v; // Defocus disk vertical radius

    void initialize()
    {
        image_height = static_cast<int>(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        center = lookfrom;

        // Determine viewport dimensions.
        auto theta = (PI / 180.0) * (vfov);
        auto h = tan(theta / 2);
        auto viewport_height = 2 * h * focus_dist;
        auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

        // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
        w = linalg::normalize(lookfrom - lookat);
        u = linalg::normalize(cross(vup, w));
        v = linalg::cross(w, u);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        vec3 viewport_u = viewport_width * u;   // Vector across viewport horizontal edge
        vec3 viewport_v = viewport_height * -v; // Vector down viewport vertical edge

        // Calculate the horizontal and vertical delta vectors to the next pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel.
        auto viewport_upper_left = center - (focus_dist * w) - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    vec3 pixel_sample_square() const
    {
        // Returns a random point in the square surrounding a pixel at the origin.
        auto px = -0.5 + uniform();
        auto py = -0.5 + uniform();
        return (px * pixel_delta_u) + (py * pixel_delta_v);
    }
};