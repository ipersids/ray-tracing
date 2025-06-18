/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 01:51:01 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/18 23:12:05 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Computes intersections between a ray and a plane.
 *
 * Transforms the ray into the plane's local space and checks if it is parallel.
 * If not parallel, computes the intersection point(s) and returns them.
 *
 * @param pl Pointer to the plane structure.
 * @param ray The ray to test for intersection.
 * @return t_intersections Structure containing intersection distances (t vals)
 */
t_intersections	rt_intersect_plane(const t_plane *pl, t_ray ray)
{
	t_intersections	xs;

	xs.count = 0;
	xs.obj_type = ELEMENT_PLANE;
	ray.dir = matrix_multiply_vector(pl->inv_transform, ray.dir);
	ray.orig = matrix_multiply_point(pl->inv_transform, ray.orig);
	if (fabsf(ray.dir.y) < EPSILON)
		return (xs);
	xs.count = 1;
	xs.t[0] = -ray.orig.y / ray.dir.y;
	xs.t[1] = xs.t[0];
	return (xs);
}

/**
 * @brief Computes the normal vector at a point on the plane.
 *
 * Returns the normalized world-space normal vector for the plane.
 *
 * @param pl Pointer to the plane structure.
 * @return t_vec3 The normal vector at the given point.
 */
t_vec3	rt_plane_normal_at(const t_plane *pl)
{
	const t_vec3	canonical_normal = (t_vec3){0.0f, 1.0f, 0.0f};
	t_vec3			world_normal;

	world_normal = matrix_multiply_vector(pl->inv_transpose, canonical_normal);
	return (normalize(world_normal));
}

t_vec3	rt_plane_bumped_normal_at(mlx_image_t *tex, t_plane *pl, t_point *p)
{
	t_vec3	normal;

	(void)tex;
	(void)p;
	normal = rt_plane_normal_at(pl);
	return (normal);
}
