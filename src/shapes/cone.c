/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 00:13:27 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/18 22:50:21 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_intersections	truncate_co(const t_cone *co, t_intersect_vars *vars,
							const t_ray *ray);
static void				handle_discriminant(t_intersect_vars *vars);

/**
 * @brief 
 * 
 * Infinite double cone: x² + z² = y²
 * `a` = 0 (ray parallel to cone surface):
 * 	- `a` and `b` are zero = ray miss
 * 	- `a` is zero but `b` is not: t = -c/(2.0f*vars.b)
 * `a` is nonzero:
 * 	- discriminant truly negative (ray missed)
 *  - discriminant tiny negative or zero  (tangent case): t = -c/(2.0f*vars.b)
 *  - discriminant > zero: two distinct roots
 * 
 * @param co 
 * @param r 
 * @return t_intersections 
 * @note A tangent means the ray touches the surface at exactly one point 
 * 		 without crossing through it (discriminant = 0)
 */
t_intersections	rt_intersect_cone(const t_cone *co, t_ray r)
{
	t_intersections		res;
	t_intersect_vars	v;

	res.count = 0;
	res.obj_type = ELEMENT_CONE;
	r.dir = matrix_multiply_vector(co->inv_transform, r.dir);
	r.orig = matrix_multiply_point(co->inv_transform, r.orig);
	v.a = r.dir.x * r.dir.x - r.dir.y * r.dir.y + r.dir.z * r.dir.z;
	v.b = 2.0f * (r.orig.x * r.dir.x - r.orig.y * r.dir.y + r.orig.z * r.dir.z);
	v.c = r.orig.x * r.orig.x - r.orig.y * r.orig.y + r.orig.z * r.orig.z;
	v.t1 = -v.c / (2.0f * v.b);
	if (equal(v.a, 0.0f))
	{
		if (equal(v.b, 0.0f))
			return (res);
		res.t[res.count++] = v.t1;
		res.t[res.count++] = v.t1;
		return (res);
	}
	v.disc = v.b * v.b - 4.0f * v.a * v.c;
	if (v.disc < -EPSILON)
		return (res);
	handle_discriminant(&v);
	res = truncate_co(co, &v, &r);
	return (res);
}

t_vec3	rt_cone_normal_at(const t_cone *co, t_point w_point)
{
	t_vec3	obj_point;
	t_vec3	obj_normal;
	t_vec3	world_normal;
	float	distance;

	obj_point = matrix_multiply_point(co->inv_transform, w_point);
	distance = sqrtf(obj_point.x * obj_point.x + obj_point.z * obj_point.z);
	obj_normal = (t_vec3){obj_point.x, distance, obj_point.z};
	if (distance > 0.0f)
		obj_normal.y = -obj_normal.y;
	if (magnitude(obj_normal) < EPSILON)
		return ((t_vec3){0.0f, 0.0f, 0.0f});
	world_normal = matrix_multiply_vector(co->inv_transpose, obj_normal);
	world_normal = normalize(world_normal);
	return (world_normal);
}

t_vec3	rt_cone_bumped_normal_at(mlx_image_t *tex, t_cone *co, t_point *p)
{
	t_vec3	normal;

	(void)tex;
	normal = rt_cone_normal_at(co, *p);
	return (normal);
}

static t_intersections	truncate_co(const t_cone *co, t_intersect_vars *vars,
							const t_ray *ray)
{
	t_intersections	res;

	res.count = 0;
	res.obj_type = ELEMENT_CONE;
	vars->y0 = ray->orig.y + (vars->t1 * ray->dir.y);
	if (vars->y0 > 0.0f && vars->y0 < co->height)
	{
		res.t[res.count] = vars->t1;
		res.count += 1;
	}
	vars->y1 = ray->orig.y + (vars->t2 * ray->dir.y);
	if (vars->y1 > 0.0f && vars->y1 < co->height)
	{
		res.t[res.count] = vars->t2;
		res.count += 1;
	}
	return (res);
}

static void	handle_discriminant(t_intersect_vars *vars)
{
	if (vars->disc <= EPSILON)
	{
		vars->t1 = -vars->b / (2.0f * vars->a);
		vars->t2 = vars->t1;
	}
	else
	{
		vars->t1 = (-vars->b - sqrtf(vars->disc)) / (2.0f * vars->a);
		vars->t2 = (-vars->b + sqrtf(vars->disc)) / (2.0f * vars->a);
	}
}
