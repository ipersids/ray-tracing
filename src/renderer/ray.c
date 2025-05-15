/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:38:23 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/16 01:51:01 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	ray_direction = subtractation(px_center, camera->pos);
	return ((t_ray){camera->pos, ray_direction, RAY_CAMERA});
}

/// @todo: implement function to get color of the ray
/**
 * @brief Calculates the color of a ray based on its direction.
 * 
 * This function generates a gradient color based on the normalized direction
 * of the ray. The gradient transitions from white to a sky-blue color.
 * 
 * @param ray Pointer to the ray structure.
 * @return t_color The calculated color for the ray.
 */
t_color	rt_get_ray_color(const t_ray *ray)
{
	t_vec3	ray_dir_norm;
	t_color	col;
	float	a;

	ray_dir_norm = normalize(ray->dir);
	a = 0.5f * (ray_dir_norm.y + 1.0);
	col = addition(
			multiplication((t_vec3){1.0f, 1.0f, 1.0f}, 1.0f - a),
			multiplication((t_vec3){0.5f, 0.7f, 1.0f}, a));
	return (col);
}
