/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_caps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 22:17:11 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/06 00:24:29 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static inline bool	check_cap(const t_ray *ray, const float t);

/* --------------------------- Public Functions ---------------------------- */

t_intersections	rt_intersect_cap(const t_cylinder *cy, t_ray ray)
{
	t_intersections	res;
	float			t;

	res.count = 0;
	res.obj_type = ELEMENT_CYLINDER_CAP;
	if (equal(ray.dir.y, 0.0f))
		return (res);
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

t_vec3	rt_cap_normal_at(const t_cylinder *cy, t_point w_point)
{
	t_vec3	obj_point;
	t_vec3	obj_normal;
	t_vec3	world_normal;
	float	dist;

	obj_point = matrix_multiply_point(cy->inv_transform, w_point);
	dist = (obj_point.x * obj_point.x) + (obj_point.z * obj_point.z);
	if (dist < 1.0f && (obj_point.y >= cy->half_height - EPSILON))
	{
		obj_normal = (t_vec3){0.0f, 1.0f, 0.0f};
		world_normal = matrix_multiply_vector(cy->inv_transpose, obj_normal);
		return (normalize(world_normal));
	}
	if (dist < 1.0f && (obj_point.y <= -cy->half_height + EPSILON))
	{
		obj_normal = (t_vec3){0.0f, -1.0f, 0.0f};
		world_normal = matrix_multiply_vector(cy->inv_transpose, obj_normal);
		return (normalize(world_normal));
	}
	obj_normal = (t_vec3){obj_point.x, 0.0f, obj_point.z};
	world_normal = matrix_multiply_vector(cy->inv_transpose, obj_normal);
	return (normalize(world_normal));
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
