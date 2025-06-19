/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reerikai <reerikai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:30:27 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/19 16:58:27 by reerikai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

/**
 * @brief Truncates intersections to the finite height of the cylinder.
 * @param cy Pointer to the cylinder structure.
 * @param vars Pointer to the intersection variables.
 * @param ray Pointer to the ray structure.
 * @return t_intersections Structure containing valid intersection data.
 */
static t_intersections	truncate_cy(const t_cylinder *cy,
							t_intersect_vars *vars, const t_ray *ray);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Computes intersections of a ray with a finite cylinder.
 *
 * Transforms the ray into object space, solves the quadratic equation for
 * intersection, and checks if the intersection points are within the cylinder
 * finite height. Returns the intersection distances (t values) if they exist.
 *
 * @param cy Pointer to the cylinder structure.
 * @param ray The ray to test for intersection.
 * @return t_intersections Structure containing intersection data.
 */
t_intersections	rt_intersect_cylinder(const t_cylinder *cy, t_ray ray)
{
	t_intersections		res;
	t_intersect_vars	vars;

	res.count = 0;
	res.obj_type = ELEMENT_CYLINDER;
	ray.dir = matrix_multiply_vector(cy->inv_transform, ray.dir);
	ray.orig = matrix_multiply_point(cy->inv_transform, ray.orig);
	vars.a = (ray.dir.x * ray.dir.x) + (ray.dir.z * ray.dir.z);
	if (equal(vars.a, 0.0f))
		return (res);
	vars.b = (2 * ray.orig.x * ray.dir.x) + (2 * ray.orig.z * ray.dir.z);
	vars.c = (ray.orig.x * ray.orig.x) + (ray.orig.z * ray.orig.z) - 1.0f;
	vars.disc = (vars.b * vars.b) - (4 * vars.a * vars.c);
	if (vars.disc < 0.0f)
		return (res);
	vars.t1 = (-vars.b - sqrtf(vars.disc)) / (2 * vars.a);
	vars.t2 = (-vars.b + sqrtf(vars.disc)) / (2 * vars.a);
	if (vars.t1 > vars.t2)
		swapf(&vars.t1, &vars.t2);
	res = truncate_cy(cy, &vars, &ray);
	return (res);
}

/**
 * @brief Computes the normal vector at a point on the cylinder's surface.
 *
 * Transforms the point into object space, calculates the normal,
 * and transforms it back to world space.
 *
 * @param cy Pointer to the cylinder structure.
 * @param w_point The point in world coordinates.
 * @return t_vec3 The normal vector at the given point.
 */
t_vec3	rt_cylinder_normal_at(const t_cylinder *cy, t_point w_point)
{
	t_vec3	obj_point;
	t_vec3	obj_normal;
	t_vec3	world_normal;

	obj_point = matrix_multiply_point(cy->inv_transform, w_point);
	obj_normal = (t_vec3){obj_point.x, 0.0f, obj_point.z};
	world_normal = matrix_multiply_vector(cy->inv_transpose, obj_normal);
	world_normal = normalize(world_normal);
	return (world_normal);
}

t_vec3	rt_cylinder_bumped_normal_at(mlx_image_t *tex, t_cylinder *cy, t_point *p)
{
	t_vec3	normal;

	(void)tex;
	normal = rt_cylinder_normal_at(cy, *p);
	return (normal);
}

/* ------------------- Private Function Implementation --------------------- */

static t_intersections	truncate_cy(const t_cylinder *cy,
							t_intersect_vars *vars, const t_ray *ray)
{
	t_intersections	res;

	res.count = 0;
	res.obj_type = ELEMENT_CYLINDER;
	vars->y0 = ray->orig.y + (vars->t1 * ray->dir.y);
	if (vars->y0 > -cy->half_height && vars->y0 < cy->half_height)
	{
		res.t[res.count] = vars->t1;
		res.count += 1;
	}
	vars->y1 = ray->orig.y + (vars->t2 * ray->dir.y);
	if (vars->y1 > -cy->half_height && vars->y1 < cy->half_height)
	{
		res.t[res.count] = vars->t2;
		res.count += 1;
	}
	return (res);
}
