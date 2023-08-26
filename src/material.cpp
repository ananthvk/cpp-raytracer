#include "material.hpp"

LambertianDiffuse::LambertianDiffuse() : albedo(color(0.5, 0.5, 0.5)) {}

LambertianDiffuse::LambertianDiffuse(const color &albedo) : albedo(albedo) {}

MaterialInteraction LambertianDiffuse::interact(const RayParams &params,
                                                const Intersection &intersect) const
{
    // Diffuse materials
    // In these materials, rays which are incident on the surface
    // are randomly reflected in all directions.
    MaterialInteraction interaction;
    auto scatter_direction = intersect.local_normal + random_in_unit_sphere();
    // To prevent cases where the direction becomes zero when the random vector is exactly opposite
    // to the normal
    if (is_zero_vector(scatter_direction))
        scatter_direction = intersect.local_normal;
    // If the unit vector and the ray are not on the same side, flip the
    // vector
    if (linalg::dot(intersect.local_normal, scatter_direction) < 0.0)
    {
        scatter_direction = -scatter_direction;
    }
    interaction.additional_rays = true;
    interaction.attenuation = albedo;
    interaction.ray = Ray(intersect.point, scatter_direction);
    return interaction;
}