/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflective_materials.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 00:52:38 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/12 00:57:34 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Highly reflective metallic surface
 * 
 * Metallic materials: gold, silver, copper, aluminum,
 * steel. Colored specular highlights, high reflectivity,
 * minimal diffuse.
 * 
 * @return t_material 
 */
t_material	init_metal_material(void)
{
	t_material	res;

	res.diffuse = 0.1f;
	res.specular = 0.9f;
	res.shininess = 300.0f;
	res.reflective = 0.8f;
	res.refractive = 1.0f;
	res.trasporancy = 0.0f;
	return (res);
}

/**
 * @brief Rough metallic surface with reduced reflectivity
 * 
 * Brushed or oxidized metals: brushed aluminum, rusted iron,
 * weathered copper. Lower reflectivity, broader specular 
 * highlights.
 * 
 * @return t_material 
 */
t_material	init_rasted_metal_material(void)
{
	t_material	res;

	res.diffuse = 0.3f;
	res.specular = 0.6f;
	res.shininess = 50.0f;
	res.reflective = 0.3f;
	res.refractive = 1.0f;
	res.trasporancy = 0.0f;
	return (res);
}

/**
 * @brief Glazed ceramic with smooth finish
 * 
 * Ceramic objects: porcelain, pottery, tiles, china.
 * Smooth glazed surface with moderate reflectivity.
 * 
 * @return t_material 
 */
t_material	init_ceramic_material(void)
{
	t_material	res;

	res.diffuse = 0.6f;
	res.specular = 0.4f;
	res.shininess = 100.0f;
	res.reflective = 0.2f;
	res.refractive = 1.5f;
	res.trasporancy = 0.0f;
	return (res);
}

/**
 * @brief Perfect mirror with maximum reflectivity
 * 
 * Mirror surfaces: bathroom mirrors, polished chrome,
 * still water. Nearly perfect reflection, minimal absorption.
 * 
 * @return t_material 
 */
t_material	init_mirror_material(void)
{
	t_material	res;

	res.diffuse = 0.0f;
	res.specular = 0.1f;
	res.shininess = 1000.0f;
	res.reflective = 0.95f;
	res.refractive = 1.0f;
	res.trasporancy = 0.0f;
	return (res);
}

