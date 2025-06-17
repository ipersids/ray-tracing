/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_uv_coordinates.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:02:01 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/18 01:02:18 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	res.tanget.x = -sinf(theta);
	res.tanget.y = 0.0f;
	res.tanget.z = cosf(theta);
	res.tanget = normalize(res.tanget);
	res.bitanget.x = cosf(theta) * cosf(phi);
	res.bitanget.y = -sinf(phi);
	res.bitanget.z = sinf(theta) * cosf(phi);
	res.bitanget = normalize(res.bitanget);
	return (res);
}
