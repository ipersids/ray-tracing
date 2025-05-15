#include "minirt.h"

/** @todo: implement function to get ray from the eye-point 
 * 
 *  @brief Calculates a ray from the eye-point (primary ray)
 * 
*/
t_ray	rt_get_ray(t_camera *camera, int32_t px, int32_t py)
{
	t_point	px_center = addition(
		camera->px00_loc, addition(
			multiplication(camera->px_delta_u, py),
			multiplication(camera->px_delta_v, px)
		)
	);

	t_vec3 ray_direction = subtractation(px_center, camera->pos);
	return ((t_ray){camera->pos, ray_direction, RAY_CAMERA});
}

/// @todo: implement function to get color of the ray
t_color	rt_get_ray_color(const t_ray *ray)
{
	t_vec3 ray_dir_norm = normalize(ray->dir);
	float a = 0.5f * (ray_dir_norm.y + 1.0);
	t_color col = addition(
		multiplication((t_vec3){1.0f, 1.0f, 1.0f}, 1.0f - a),
		multiplication((t_vec3){0.5f, 0.7f, 1.0f}, a)
	);
	return (col);
}
