/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_material.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:55:39 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/12 01:16:42 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

t_pat	set_stripe_pattern(t_color a, t_color b, float scale, float angle_rad);
t_pat	set_checker_pattern(t_color a, t_color b, float scale);
t_pat	set_gradient_pattern(t_color a, t_color b, float scale);

/**
 * @brief Sets the material for an object based on its type.
 *
 * @param ambient The ambient color to use for the material.
 * @param obj Pointer to the object whose material will be set.
 * @param type The material type.
 */

 		/*						CHECKER PATTERN						*/
 		/*		FOR SPHERES A SMALL NUMBER FOR SCALE (0.4-0.6)		*/
		/*			FOR PLANES A BIG NUMBER FOR SCALE (4-6)			*/
void	rt_set_material(t_info *rt, t_object *obj)
{
	obj->material = &rt->materials[MATERIAL_DEFAULT];
	obj->amb_component = multiply_colors(obj->color, rt->amb_intensity);
}

t_pat	set_stripe_pattern(t_color a, t_color b, float scale, float angle_rad)
{
	t_pat		pattern;
	t_matrix	scale_matrix;
	t_matrix	rot_matrix;

	scale_matrix = matrix_scaling(scale, 1.0f, 1.0f);
	rot_matrix = matrix_rotation_y(angle_rad);
	pattern.type = PATTERN_STRIPE;
	pattern.color_a = a;
	pattern.color_b = b;
	pattern.has_pattern = true;
	pattern.transform = matrix_multiply(rot_matrix, scale_matrix);
	matrix_try_inverse(pattern.transform, &pattern.inv_transform);
	return (pattern);
}

t_pat	set_checker_pattern(t_color a, t_color b, float scale)
{
	t_pat	pattern;

	pattern.type = PATTERN_CHECKER;
	pattern.color_a = a;
	pattern.color_b = b;
	pattern.has_pattern = true;
	pattern.transform = matrix_scaling(scale, scale, scale);
	matrix_try_inverse(pattern.transform, &pattern.inv_transform);
	return (pattern);
}

t_pat	set_gradient_pattern(t_color a, t_color b, float scale)
{
	t_pat	pattern;
	pattern.type = PATTERN_GRADIENT;
	pattern.color_a = a;
	pattern.color_b = b;
	pattern.has_pattern = true;
	pattern.transform = matrix_scaling(scale, 1.0f, 1.0f);
	matrix_try_inverse(pattern.transform, &pattern.inv_transform);
	return (pattern);
}
