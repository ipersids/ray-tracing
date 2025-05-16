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
	ray_direction = subtraction(px_center, camera->pos);
	return ((t_ray){camera->pos, ray_direction, RAY_CAMERA});
}

/// @todo: implement function to get color of the ray
t_color	ray_color(t_ray ray)
{
	t_color	color;
	t_color	white;
	t_color	blue;
	t_vec3	unit_direction;
	float	a;

	/// @todo move logic for hitting objects to the camera
	if (hit_sphere((t_vec3){-50.0f, 0.0f, 70.0f}, 10, ray)) /// @test
		return ((t_color){1.0f, 0.0f, 0.0f});
	unit_direction = normalize(ray.dir);
	a = 0.5 * (unit_direction.y + 1.0);
	white = (t_color){1.0, 1.0, 1.0};
	blue = (t_color){0.5, 0.7, 1.0};
	color = addition(multiplication(white, 1.0 - a), multiplication(blue, a));
	return (color);
}