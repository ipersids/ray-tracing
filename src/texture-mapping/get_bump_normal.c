/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bump_normal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 23:32:44 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/18 01:28:31 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	rt_sphere_bumped_normal(mlx_image_t *tex, t_sphere *sp, t_point *p)
{
	t_uv_vars	uv;
	t_gradient	var;
	t_vec3		perturbation;
	t_vec3		normal;
	t_vec3		bamped_normal;

	uv = rt_get_spherical_uv(sp, p);
	var = rt_get_gradient(tex, uv.u, uv.v);
	perturbation = addition(
		multiplication(uv.tanget, var.gradient_u),
		multiplication(uv.bitanget, var.gradient_v)
	);
	perturbation = multiplication(perturbation, BUMP_FACTOR);
	perturbation = matrix_multiply_vector(sp->inv_transpose, perturbation);
	normal = sphere_normal_at(sp, *p);
	bamped_normal = addition(normal, perturbation);
	bamped_normal = normalize(bamped_normal);
	return (bamped_normal);
}
