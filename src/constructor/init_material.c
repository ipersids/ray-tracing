/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_material.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:39:26 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/06 23:55:48 by ipersids         ###   ########.fr       */
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

	ft_memset(&res, 0, sizeof(t_material));
	res.ambient_comp = ambient;
	res.color = mcolor;
	res.final_color = ambient;
	res.diffuse = 0.9;
	res.specular = 0.9;
	res.shininess = 200.0;
	res.type = n;
	return (res);
}
