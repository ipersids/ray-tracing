/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse_materials.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 00:51:38 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/12 21:29:50 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

t_material	init_default_material(void)
{
	t_material	res;

	res.diffuse = 0.9f;
	res.specular = 0.9f;
	res.shininess = 200.0f;
	res.reflective = 0.0f;
	res.refractive = 1.0f;
	res.transparency = 0.0f;
	return (res);
}

/**
 * @brief Completely diffuse, no shine
 * 
 * Natural, organic surfaces: chalk, unfinished wood, 
 * paper, concrete. High diffuse, zero specular.
 * 
 * @return t_material 
 */
t_material	init_lambertian_material(void)
{
	t_material	res;

	res.diffuse = 0.9f;
	res.specular = 0.0f;
	res.shininess = 1.0f;
	res.reflective = 0.0f;
	res.refractive = 1.0f;
	res.transparency = 0.0f;
	return (res);
}

/**
 * @brief Glossy plastic with balanced diffuse and specular
 * 
 * Shiny plastic objects: toys, car bumpers, phone cases.
 * Balanced diffuse/specular, moderate shininess, some reflection.
 * 
 * @return t_material 
 */
t_material	init_plastic_material(void)
{
	t_material	res;

	res.diffuse = 0.7f;
	res.specular = 0.5f;
	res.shininess = 80.0f;
	res.reflective = 0.015f;
	res.refractive = 1.4f;
	res.transparency = 0.0f;
	return (res);
}
