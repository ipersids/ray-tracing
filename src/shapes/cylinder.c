/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:30:27 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/05 14:11:26 by ipersids         ###   ########.fr       */
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
