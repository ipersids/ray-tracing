/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:30:27 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/05 14:28:53 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

t_intersections	rt_intersect_cylinder(const t_cylinder *cy, t_ray ray)
{
	t_intersections		res;
	t_intersect_vars	vars;

	res.count = 0;
	ray.dir = matrix_multiply_vector(cy->inv_transform, ray.dir);
	ray.orig = matrix_multiply_point(cy->inv_transform, ray.orig);
	vars.a = (ray.dir.x * ray.dir.x) + (ray.dir.z * ray.dir.z);
	vars.b = (2 * ray.orig.x * ray.dir.x) + (2 * ray.orig.z * ray.dir.z);
	vars.c = (ray.orig.x * ray.orig.x) + (ray.orig.z * ray.orig.z) - 1.0f;
	vars.disc = (vars.b * vars.b) - (4 * vars.a * vars.c);
	if (equal(vars.disc, 0.0f))
		return (res);
	res.t[0] = (-vars.b - sqrtf(vars.disc)) / (2 * vars.a);
	res.t[1] = (-vars.b + sqrtf(vars.disc)) / (2 * vars.a);
	res.count = 2;
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

// t_vec3	sphere_normal_at(t_sphere *sp, t_point world_point)
// {
// 	t_vec3		obj_point;
// 	t_vec3		obj_normal;
// 	t_vec3		world_normal;

// 	obj_point = matrix_multiply_point(sp->inv_transform, world_point);
// 	obj_normal = subtraction(obj_point, sp->center);
// 	world_normal = matrix_multiply_vector(sp->inv_transpose, obj_normal);
// 	world_normal = normalize(world_normal);
// 	return (world_normal);
// }