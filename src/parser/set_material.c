/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_material.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:55:39 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/01 13:00:10 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

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
	}
}
