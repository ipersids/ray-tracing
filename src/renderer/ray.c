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
// t_ray	rt_get_ray(t_camera *cam, int32_t px, int32_t py)
// {
// 	t_point	px_center;
// 	t_vec3	ray_direction;

// 	px_center = addition(cam->px00_loc, addition(
// 				multiplication(cam->px_delta_u, px),
// 				multiplication(cam->px_delta_v, py)));
// 	ray_direction = normalize(subtraction(px_center, cam->pos));
// 	return ((t_ray){cam->pos, ray_direction, RAY_CAMERA});
// }

t_ray	rt_get_ray(t_camera *cam, int32_t px, int32_t py)
{
	t_ray_vars	vars;
	t_ray		ray;
	t_vec3		canvas_point;

	vars.xoffset = ((float)px + 0.5f) * cam->pixel_size;
	vars.yoffset = ((float)py + 0.5f) * cam->pixel_size;
	vars.world_x = cam->half_width - vars.xoffset;
	vars.world_y = cam->half_height - vars.yoffset;
	canvas_point = (t_vec3){vars.world_x, vars.world_y, -1.0f};
	vars.pixel = matrix_multiply_point(cam->inv_transform, canvas_point);
	ray.orig = matrix_multiply_point(cam->inv_transform, (t_vec3){0.0f, 0.0f, 0.0f});
	ray.dir = normalize(subtraction(vars.pixel, ray.orig));
	ray.type = RAY_CAMERA;
	return (ray);
}

t_vec3	ray_hit(t_ray ray, float t)
{
	t_vec3 scaled_direction;

	scaled_direction = multiplication(ray.dir, t);
	return addition(ray.orig, scaled_direction);
}

