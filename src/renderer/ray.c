#include "minirt.h"

/** @todo: implement function to get ray from the eye-point 
 * 
 *  @brief Calculates a ray from the eye-point (primary ray)
 * 
*/
t_ray	rt_get_ray(t_camera *camera, int32_t px, int32_t py)
{
	(void)camera;
	(void)px;
	(void)py;
	return ((t_ray){{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, RAY_CAMERA});
}

/// @todo: implement function to get color of the ray
t_color	rt_get_ray_color(const t_ray *ray)
{
	(void)ray;
	return ((t_color){0.0f, 1.0f, 0.867f});
}
