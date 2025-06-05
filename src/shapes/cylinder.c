/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:30:27 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/05 12:51:54 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

// t_intersections	rt_intersect_plane(const t_plane *pl, t_ray ray)
// {
// 	t_intersections	xs;

// 	xs.count = 0;
// 	ray.dir = matrix_multiply_vector(pl->inv_transform, ray.dir);
// 	ray.orig = matrix_multiply_point(pl->inv_transform, ray.orig);
// 	if (fabsf(ray.dir.y) < EPSILON)
// 		return (xs);
// 	xs.count = 1;
// 	xs.t[0] = -ray.orig.y / ray.dir.y;
// 	xs.t[1] = xs.t[0];
// 	return (xs);
// }

t_intersections	rt_intersect_cylinder(const t_cylinder *cy, t_ray ray)
{
	t_intersections	res;
	res.count = 0;
	(void)cy;
	(void)ray;
	return (res);
}
