/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 01:51:01 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/01 10:50:12 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersections	intersect_plane(const t_plane *pl, t_ray ray)
{
	t_intersections	xs;

	xs.count = 0;
	ray.dir = matrix_multiply_vector(pl->inv_transform, ray.dir);
	ray.orig = matrix_multiply_point(pl->inv_transform, ray.orig);
	if (fabsf(ray.dir.y) < EPSILON)
		return (xs);
	xs.count = 1;
	xs.t[0] = -ray.orig.y / ray.dir.y;
	xs.t[1] = xs.t[0];
	return (xs);
}

t_vec3	plane_normal_at(const t_plane *pl)
{
	const t_vec3	canonical_normal = (t_vec3){0.0f, 1.0f, 0.0f};
	t_vec3			world_normal;

	world_normal = matrix_multiply_vector(pl->inv_transpose, canonical_normal);
	return (normalize(world_normal));
}
