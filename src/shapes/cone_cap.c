/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_cap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:30:35 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/18 23:39:43 by ipersids         ###   ########.fr       */
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
	const t_vec3	canonical_normal = (t_vec3){0.0f, 1.0f, 0.0f};
	t_vec3			world_normal;

	(void)w_point;
	world_normal = matrix_multiply_vector(co->inv_transpose, canonical_normal);
	return (normalize(world_normal));
}

t_vec3	rt_cone_cap_bumped_normal_at(mlx_image_t *tex, t_cone *co, t_point *p)
{
	t_vec3	normal;

	(void)tex;
	normal = rt_cone_cap_normal_at(co, *p);
	return (normal);
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
