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
t_ray	rt_get_ray(t_camera *camera, int32_t px, int32_t py)
{
	t_point	px_center;
	t_vec3	ray_direction;

	px_center = addition(camera->px00_loc, addition(
				multiplication(camera->px_delta_u, px),
				multiplication(camera->px_delta_v, py)));
	ray_direction = normalize(subtraction(px_center, camera->pos));
	return ((t_ray){camera->pos, ray_direction, RAY_CAMERA});
}

t_vec3	ray_hit(t_ray ray, float t)
{
	t_vec3 scaled_direction;

	scaled_direction = multiplication(ray.dir, t);
	return addition(ray.orig, scaled_direction);
}

void print_vec3(const char *label, t_vec3 v)
{
	printf("%s = (%.2f, %.2f, %.2f)\n", label, v.x, v.y, v.z);
}
