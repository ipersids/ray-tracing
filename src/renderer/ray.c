#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Calculates a primary ray from the camera's eye-point to a pixel.
 *
 * This function computes the ray direction for a given pixel on the viewport.
 * The ray originates from the camera's position and points toward the center
 * of the specified pixel.
 *
 * @param camera Pointer to the camera structure.
 * @param px The x-coordinate of the pixel.
 * @param py The y-coordinate of the pixel.
 * @return t_ray The calculated ray with origin, direction, and type.
 */
t_ray	rt_get_ray(t_camera *cam, int32_t px, int32_t py)
{
	const t_vec3	center = (t_vec3){0.0f, 0.0f, 0.0f};
	t_ray_vars		vars;
	t_ray			ray;
	t_vec3			world_point;

	vars.xoffset = ((float)px + 0.5f) * cam->pixel_size;
	vars.yoffset = ((float)py + 0.5f) * cam->pixel_size;
	vars.world_x = cam->half_width - vars.xoffset;
	vars.world_y = cam->half_height - vars.yoffset;
	world_point = (t_vec3){vars.world_x, vars.world_y, -1.0f};
	vars.pixel = matrix_multiply_point(cam->inv_transform, world_point);
	ray.orig = matrix_multiply_point(cam->inv_transform, center);
	ray.dir = normalize(subtraction(vars.pixel, ray.orig));
	ray.type = RAY_CAMERA;
	return (ray);
}

/**
 * @brief Computes the point along a ray at parameter t.
 *
 * @param ray The ray.
 * @param t The parameter value.
 * @return The point at ray.origin + t * ray.direction.
 */
t_vec3	ray_hit(t_ray ray, float t)
{
	t_vec3	scaled_direction;

	scaled_direction = multiplication(ray.dir, t);
	return (addition(ray.orig, scaled_direction));
}

/**
 * @brief Computes the reflection vector for an incoming vec and a normal.
 *
 * @param in The incoming vector.
 * @param normal The normal vector at the point of reflection.
 * @return The reflected vector.
 */
t_vec3	reflect(t_vec3 in, t_vec3 normal)
{
	t_vec3	result;
	t_vec3	scaled_norm;

	scaled_norm = multiplication(normal, 2 * dot_product(in, normal));
	result = subtraction(in, scaled_norm);
	return (result);
}
