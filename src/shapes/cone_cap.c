/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_cap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:30:35 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/07 16:23:05 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static inline bool	check_cap(const t_ray *ray, const float t, float radius);

/* --------------------------- Public Functions ---------------------------- */

t_intersections	rt_intersect_cone_cap(const t_cone *co, t_ray ray)
{
	t_intersections	res;
	float			t;

	res.count = 0;
	res.obj_type = ELEMENT_CONE_CAP;
	ray.dir = matrix_multiply_vector(co->inv_transform, ray.dir);
	ray.orig = matrix_multiply_point(co->inv_transform, ray.orig);
	t = (co->height - ray.orig.y) / ray.dir.y;
	if (t > EPSILON && check_cap(&ray, t, co->height))
	{
		res.t[res.count] = t;
		res.count += 1;
	}
	return (res);
}

t_vec3	rt_cone_cap_normal_at(const t_cone *co, t_point w_point)
{
	t_vec3	obj_point;
	t_vec3	obj_normal;
	t_vec3	world_normal;
	float	dist;

	obj_point = matrix_multiply_point(co->inv_transform, w_point);
	dist = (obj_point.x * obj_point.x) + (obj_point.z * obj_point.z);
	obj_point.y = sqrtf(obj_point.x * obj_point.x + obj_point.z * obj_point.z);
	if (obj_point.y > 0.0f)
		obj_point.y = -obj_point.y;
	if (dist < 1.0f && (obj_point.y >= co->height - EPSILON))
	{
		obj_normal = (t_vec3){0.0f, 1.0f, 0.0f};
		world_normal = matrix_multiply_vector(co->inv_transpose, obj_normal);
		return (normalize(world_normal));
	}
	obj_normal = (t_vec3){obj_point.x, obj_point.y, obj_point.z};
	world_normal = matrix_multiply_vector(co->inv_transpose, obj_normal);
	return (normalize(world_normal));
}

/* ------------------- Private Function Implementation --------------------- */

static inline bool	check_cap(const t_ray *ray, const float t, float radius)
{
	float	x;
	float	z;

	x = ray->orig.x + (t * ray->dir.x);
	z = ray->orig.z + (t * ray->dir.z);
	return (((x * x) + (z * z)) <= radius * radius);
}
