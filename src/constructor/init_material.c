/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_material.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:39:26 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/11 22:06:01 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

// static t_material	init_default_material(void);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Initializes a material with given ambient and object color.
 *
 * @param ambient Ambient color.
 * @param obj_color Object color.
 * @param type Material type.
 * @return t_material The initialized material.
 */
void	rt_init_material(t_material *materials)
{
	materials[MATERIAL_DEFAULT] = init_default_material();
}

/* ------------------- Private Function Implementation --------------------- */

t_material	init_default_material(void)
{
	t_material	res;

	res.diffuse = 0.9f;
	res.specular = 0.9f;
	res.shininess = 200.0f;
	res.reflective = 0.0f;
	res.refractive = 1.0f;
	res.trasporancy = 0.0f;
	return (res);
}
