/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_uv_coordinates.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:02:01 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/19 16:38:40 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_uv_vars	rt_get_uv_coordinates(t_object *obj, t_point *point)
{
	if (ELEMENT_SPHERE == obj->id)
		return (rt_get_spherical_uv(&obj->sp, point));
	return (rt_get_planar_uv(&obj->pl, point));
}

/**
 * @brief 
 * 
 * Spherical angles:
 * 	- Theta (θ): Horizontal angle around the sphere (longitude)
 * 	- Phi (φ): Vertical angle from top to bottom (latitude)
 * 
 * @param local_point 
 * @param u 
 * @param v 
 */
t_uv_vars	rt_get_spherical_uv(t_sphere *sp, t_point *point)
{
	const float	u_rotate = 0.5f;
	float		theta;
	float		phi;
	t_point		local_point;
	t_uv_vars	res;

	local_point = normalize(matrix_multiply_point(sp->inv_transform, *point));
	theta = atan2f(local_point.x, local_point.z) + M_PI;
	phi = acosf(local_point.y);
	res.u = 1.0f - (theta / (2 * M_PI));
	res.u = fmodf(res.u + u_rotate, 1.0f);
	res.v = phi / M_PI;
	res.tangent.x = -sinf(theta);
	res.tangent.y = 0.0f;
	res.tangent.z = cosf(theta);
	res.tangent = normalize(res.tangent);
	res.bitangent.x = cosf(theta) * cosf(phi);
	res.bitangent.y = -sinf(phi);
	res.bitangent.z = sinf(theta) * cosf(phi);
	res.bitangent = normalize(res.bitangent);
	return (res);
}

t_uv_vars	rt_get_planar_uv(t_plane *pl, t_point *point)
{
	const float	scale = 0.015f;
    t_point     local_point;
    t_uv_vars   res;

    local_point = matrix_multiply_point(pl->inv_transform, *point);
    res.u = fmodf(local_point.x * scale, 1.0f);
	if (0.0f > res.u)
		res.u = res.u + 1.0f;
	res.v = fmodf(local_point.z * scale, 1.0f);
	if (0.0f > res.v)
		res.v = res.v + 1.0f;
	res.tangent = (t_vec3){1.0f, 0.0f, 0.0f};
	res.bitangent = (t_vec3){0.0f, 0.0f, 1.0f};
    return (res);
}
