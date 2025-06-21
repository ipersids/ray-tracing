/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_cap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:30:35 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/21 11:40:53 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static inline bool	check_cap(const t_ray *ray, const float t, float radius);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Computes intersections between a ray and the cap of a cone.
 * 
 * @param co Pointer to the cone structure.
 * @param ray The ray to test for intersection.
 * @return t_intersections Structure containing intersection data.
 */
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

/**
 * @brief Computes the normal vector at a point on the cone's cap.
 *
 * Returns the transformed canonical normal for the cap in world coordinates.
 *
 * @param co Pointer to the cone structure.
 * @param w_point The point in world coordinates (unused).
 * @return The normal vector at the given point.
 */
t_vec3	rt_cone_cap_normal_at(const t_cone *co)
{
	const t_vec3	canonical_normal = (t_vec3){0.0f, 1.0f, 0.0f};
	t_vec3			world_normal;

	world_normal = matrix_multiply_vector(co->inv_transpose, canonical_normal);
	return (normalize(world_normal));
}


t_vec3	rt_cone_cap_bumped_normal_at(mlx_image_t *tex, t_cone *co, t_point *p)
{
	t_vec3	normal;

	(void)tex;
	(void)p;
	normal = rt_cone_cap_normal_at(co);
	return (normal);
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Checks if a point at parameter t on the ray is within the cap radius.
 *
 * @param ray Pointer to the ray.
 * @param t The parameter value along the ray.
 * @param radius The radius of the cap.
 * @return true if the point is within the cap, false otherwise.
 */
static inline bool	check_cap(const t_ray *ray, const float t, float radius)
{
	float	x;
	float	z;

	x = ray->orig.x + (t * ray->dir.x);
	z = ray->orig.z + (t * ray->dir.z);
	return (((x * x) + (z * z)) <= radius * radius);
}
