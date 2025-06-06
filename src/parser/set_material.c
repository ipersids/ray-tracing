/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_material.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reerikai <reerikai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:55:39 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/06 19:27:00 by reerikai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

t_pat	set_stripe_pattern(t_color a, t_color b, float scale, float angle_rad);
t_pat	set_checker_pattern(t_color a, t_color b, float scale);
t_pat	set_gradient_pattern(t_color a, t_color b, float scale);

void	set_glass(t_object *obj);

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
void	rt_set_material(t_color ambient, t_object *obj, t_mtype type)
{
	if (ELEMENT_SPHERE == obj->id)
	{
		obj->sp.material = rt_init_material(ambient, obj->sp.color, type);
		obj->material = &obj->sp.material;
		set_glass(obj);
		obj->material->reflective = 0.5;
		//obj->material->pattern = set_stripe_pattern(BLACK, WHITE, 0.01f, M_PI / 3);
	}
	else if (ELEMENT_CYLINDER == obj->id)
	{
		obj->cy.material = rt_init_material(ambient, obj->cy.color, type);
		obj->material = &obj->cy.material;
		obj->material->reflective = 0.5;
	}
	else if (ELEMENT_PLANE == obj->id)
	{
		obj->pl.material = rt_init_material(ambient, obj->pl.color, type);
		obj->material = &obj->pl.material;
		//obj->material->reflective = 0.6f;
		obj->material->pattern = set_checker_pattern(WHITE, BLACK, 10.0f);
	}
}

void	set_glass(t_object *obj)
{
	obj->material->refract_ind = 1.5;
	obj->material->transparency = 1.0;
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
