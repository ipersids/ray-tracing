/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_material.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reerikai <reerikai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:55:39 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/03 15:36:35 by reerikai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

static t_pat	stripe_pattern(t_color a, t_color b, t_pattype type);

/**
 * @brief Sets the material for an object based on its type.
 *
 * @param ambient The ambient color to use for the material.
 * @param obj Pointer to the object whose material will be set.
 * @param type The material type.
 */
void	rt_set_material(t_color ambient, t_object *obj, t_mtype type)
{
	if (ELEMENT_SPHERE == obj->id)
	{
		obj->sp.material = rt_init_material(ambient, obj->sp.color, type);
		obj->material = &obj->sp.material;
		obj->material->pattern = stripe_pattern(WHITE, BLACK, PATTERN_STRIPE);
	}
	else if (ELEMENT_CYLINDER == obj->id)
	{
		obj->cy.material = rt_init_material(ambient, obj->cy.color, type);
		obj->material = &obj->cy.material;
	}
	else if (ELEMENT_PLANE == obj->id)
	{
		obj->pl.material = rt_init_material(ambient, obj->pl.color, type);
		obj->material = &obj->pl.material;
		obj->material->pattern = stripe_pattern(RED, GREEN, PATTERN_STRIPE);
	}
}

static t_pat	stripe_pattern(t_color a, t_color b, t_pattype type)
{
	t_pat	pattern;

	pattern.type = type;
	pattern.color_a = a;
	pattern.color_b = b;
	pattern.has_pattern = true;
	pattern.transform = matrix_identity();
	//pattern.transform = matrix_rotation_y(M_PI / 4);
	//pattern.transform = matrix_scaling(0.6f, 0.2f, 1.0f);
	matrix_try_inverse(pattern.transform, &pattern.inv_transform);
	return (pattern);
}
