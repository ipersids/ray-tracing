/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_material.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reerikai <reerikai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:39:26 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/06 18:47:50 by reerikai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static t_material	init_default(t_color ambient, t_color mcolor, t_mtype n);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Initializes a material with given ambient and object color.
 *
 * @param ambient Ambient color.
 * @param obj_color Object color.
 * @param type Material type.
 * @return t_material The initialized material.
 */
t_material	rt_init_material(t_color ambient, t_color obj_color, t_mtype type)
{
	t_color	ambient_component;

	ambient_component = multiply_colors(ambient, obj_color);
	if (MATERIAL_DEFAULT == type)
		return (init_default(ambient_component, obj_color, type));
	return (init_default(ambient_component, obj_color, MATERIAL_DEFAULT));
}

/* ------------------- Private Function Implementation --------------------- */

static t_material	init_default(t_color ambient, t_color mcolor, t_mtype n)
{
	t_material	res;

	res.ambient_comp = ambient;
	res.color = mcolor;
	res.final_color = ambient;
	res.diffuse = 0.9;
	res.specular = 0.9;
	res.shininess = 200.0;
	res.type = n;
	res.transparency = 0.0;
	res.refract_ind = 1.0;
	return (res);
}
