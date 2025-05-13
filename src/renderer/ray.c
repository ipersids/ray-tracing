/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 02:04:21 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/13 02:04:34 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/// @todo: implement function to get ray from the eye-point
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
