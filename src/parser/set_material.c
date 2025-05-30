/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_material.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:55:39 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/30 15:38:55 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
