/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refractive_materials.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 00:53:58 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/12 00:57:29 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Transparent glass-like material with refraction
 * 
 * Clear transparent materials: window glass, crystal, 
 * clear acrylic. High transparency, refraction,
 * minimal absorption.
 * 
 * @return t_material 
 */
t_material	init_glass_material(void)
{
	t_material	res;

	res.diffuse = 0.0f;
	res.specular = 0.9f;
	res.shininess = 300.0f;
	res.reflective = 0.1f;
	res.refractive = 1.52f;
	res.trasporancy = 0.9f;
	return (res);
}

/**
 * @brief Highly refractive precious stone
 * 
 * Precious gems: diamond, ruby, sapphire, emerald.
 * Very high refraction, excellent clarity, 
 * brilliant reflections.
 * 
 * @return t_material 
 */
t_material	init_diamond_material(void)
{
	t_material	res;

	res.diffuse = 0.0f;
	res.specular = 1.0f;
	res.shininess = 500.0f;
	res.reflective = 0.2f;
	res.refractive = 2.42f;
	res.trasporancy = 0.95f;
	return (res);
}

/**
 * @brief Water-like material with natural refraction
 * 
 * Liquid water: pools, rivers, rain drops.
 * Transparent with natural water refraction index.
 * 
 * @return t_material 
 */
t_material	init_water_material(void)
{
	t_material	res;

	res.diffuse = 0.1f;
	res.specular = 0.8f;
	res.shininess = 200.0f;
	res.reflective = 0.2f;
	res.refractive = 1.33f;
	res.trasporancy = 0.8f;
	return (res);
}

/**
 * @brief Ice with crystalline properties
 * 
 * Frozen water: ice cubes, icicles, frozen surfaces.
 * Clear but slightly cloudy, good reflectivity.
 * 
 * @return t_material 
 */
t_material	init_ice_material(void)
{
	t_material	res;

	res.diffuse = 0.2f;
	res.specular = 0.7f;
	res.shininess = 150.0f;
	res.reflective = 0.3f;
	res.refractive = 1.31f;
	res.trasporancy = 0.7f;
	return (res);
}
