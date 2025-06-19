/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_caps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 22:17:11 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/18 23:49:09 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

/**
 * @brief Checks if a given intersection t is within the cap's radius.
 * @param ray Pointer to the ray structure.
 * @param t The intersection distance along the ray.
 * @return true if the intersection is within the cap, false otherwise.
 */
static inline bool	check_cap(const t_ray *ray, const float t);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Computes intersections of a ray with the end caps of a cylinder.
 *
 * Checks for intersection with both the top and bottom caps of the cylinder,
 * and returns the intersection distances (t values) if they exist.
 *
 * @param cy Pointer to the cylinder structure.
 * @param ray The ray to test for intersection.
 * @return t_intersections Structure containing intersection data.
 */
t_intersections	rt_intersect_cylinder_cap(const t_cylinder *cy, t_ray ray)
{
	t_intersections	res;
	float			t;

	res.count = 0;
	res.obj_type = ELEMENT_CYLINDER_CAP;
	ray.dir = matrix_multiply_vector(cy->inv_transform, ray.dir);
	ray.orig = matrix_multiply_point(cy->inv_transform, ray.orig);
	t = (-cy->half_height - ray.orig.y) / ray.dir.y;
	if (t > EPSILON && check_cap(&ray, t))
	{
		res.t[res.count] = t;
		res.count += 1;
	}
	t = (cy->half_height - ray.orig.y) / ray.dir.y;
	if (t > EPSILON && check_cap(&ray, t))
	{
		res.t[res.count] = t;
		res.count += 1;
	}
	return (res);
}

/**
 * @brief Computes the normal vector at a point on a cylinder cap.
 *
 * Determines if the point is on the top or bottom cap and returns the
 * corresponding normal in world coordinates.
 *
 * @param cy Pointer to the cylinder structure.
 * @param w_point The point in world coordinates.
 * @return t_vec3 The normal vector at the given point.
 */
t_vec3	rt_cylinder_cap_normal_at(const t_cylinder *cy, t_point point)
{
	t_vec3	obj_point;
	t_vec3	canonical_normal;
	t_vec3	world_normal;

	obj_point = matrix_multiply_point(cy->inv_transform, point);
	if (obj_point.y > 0.0f)
		canonical_normal = (t_vec3){0.0f, 1.0f, 0.0f};
	else
		canonical_normal = (t_vec3){0.0f, -1.0f, 0.0f};
	world_normal = matrix_multiply_vector(cy->inv_transpose, canonical_normal);
	return (normalize(world_normal));
}

t_vec3	rt_cap_bumped_normal_at(mlx_image_t *tex, t_cylinder *cy, t_point *p)
{
	t_vec3	normal;

	(void)tex;
	normal = rt_cylinder_cap_normal_at(cy, *p);
	return (normal);
}

/* ------------------- Private Function Implementation --------------------- */

static inline bool	check_cap(const t_ray *ray, const float t)
{
	float	x;
	float	z;

	x = ray->orig.x + (t * ray->dir.x);
	z = ray->orig.z + (t * ray->dir.z);
	return (((x * x) + (z * z)) <= 1.0f);
}
