/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reerikai <reerikai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:25:04 by reerikai          #+#    #+#             */
/*   Updated: 2025/06/23 14:25:05 by reerikai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersections	intersect_sphere(t_sphere sphere, t_ray ray)
{
	const t_point		center = (t_point){0.0f, 0.0f, 0.0f};
	t_intersections		result;
	t_vec3				oc;
	t_intersect_vars	vars;

	ray.dir = matrix_multiply_vector(sphere.inv_transform, ray.dir);
	ray.orig = matrix_multiply_point(sphere.inv_transform, ray.orig);
	oc = subtraction(ray.orig, center);
	vars.a = dot_product(ray.dir, ray.dir);
	vars.b = 2.0 * dot_product(ray.dir, oc);
	vars.c = dot_product(oc, oc) - 1.0f;
	vars.disc = (vars.b * vars.b) - (4 * vars.a * vars.c);
	result.count = 0;
	result.obj_type = ELEMENT_SPHERE;
	if (vars.disc < 0.0f)
		return (result);
	vars.t1 = (-vars.b - sqrtf(vars.disc)) / (2.0 * vars.a);
	vars.t2 = (-vars.b + sqrtf(vars.disc)) / (2.0 * vars.a);
	result.t[0] = vars.t1;
	result.t[1] = vars.t2;
	result.count = 2;
	return (result);
}

t_vec3	sphere_normal_at(t_sphere *sp, t_point world_point)
{
	const t_point	center = (t_point){0.0f, 0.0f, 0.0f};
	t_vec3			obj_point;
	t_vec3			obj_normal;
	t_vec3			world_normal;

	obj_point = matrix_multiply_point(sp->inv_transform, world_point);
	obj_normal = subtraction(obj_point, center);
	world_normal = matrix_multiply_vector(sp->inv_transpose, obj_normal);
	world_normal = normalize(world_normal);
	return (world_normal);
}

t_vec3	rt_sphere_bumped_normal_at(mlx_image_t *tex, t_sphere *sp, t_point *p)
{
	t_uv_vars	uv;
	t_gradient	var;
	t_vec3		perturbation;
	t_vec3		normal;
	t_vec3		bumped_normal;

	uv = rt_get_spherical_uv(sp, p);
	var = rt_get_gradient(tex, uv.u, uv.v);
	perturbation = addition(
			multiplication(uv.tangent, var.gradient_u),
			multiplication(uv.bitangent, var.gradient_v)
			);
	perturbation = multiplication(perturbation, BUMP_FACTOR);
	perturbation = matrix_multiply_vector(sp->inv_transpose, perturbation);
	normal = sphere_normal_at(sp, *p);
	bumped_normal = addition(normal, perturbation);
	bumped_normal = normalize(bumped_normal);
	return (bumped_normal);
}
