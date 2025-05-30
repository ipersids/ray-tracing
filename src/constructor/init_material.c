/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_material.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:39:26 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/30 15:59:21 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_material init_default(t_color ambient, t_color mcolor, t_mtype n);

t_material	rt_init_material(t_color ambient, t_color obj_color, t_mtype type)
{
	t_color	ambient_component;

	ambient_component = multiply_colors(ambient, obj_color);
	if (MATERIAL_DEFAULT == type)
		return (init_default(ambient_component, obj_color, type));
	return (init_default(ambient_component, obj_color, MATERIAL_DEFAULT));
}

static t_material init_default(t_color ambient, t_color mcolor, t_mtype n)
{
	t_material	res;

	res.ambient_comp = ambient;
	res.color = mcolor;
	res.final_color = ambient;
	res.diffuse = 0.9;
	res.specular = 0.9;
	res.shininess = 200.0;
	res.type = n;
	return (res);
}
