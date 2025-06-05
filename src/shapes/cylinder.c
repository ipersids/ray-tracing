/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:30:27 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/05 23:33:55 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static void				swapf(float *t1, float *t2);
static t_intersections	truncate_cy(const t_cylinder *cy,
							t_intersect_vars *vars, const t_ray *ray);

/* --------------------------- Public Functions ---------------------------- */

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

/* ------------------- Private Function Implementation --------------------- */

static void	swapf(float *t1, float *t2)
{
	float	tmp;

	tmp = *t1;
	*t1 = *t2;
	*t2 = tmp;
}

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
