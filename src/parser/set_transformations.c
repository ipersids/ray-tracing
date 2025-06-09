/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_transformations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:51:04 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/09 12:41:49 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Sets up transformations and materials for all objects in the scene.
 * 
 * @param rt Pointer to the main program structure.
 * @return int 0 on success, or an error code on failure.
 */
int	rt_set_transformations(t_info *rt)
{
	size_t	i;
	int		exit_code;

	i = 0;
	exit_code = 0;
	if (0 != rt_update_transform(rt, NULL, ELEMENT_CAMERA))
		return (ERR_CAMERA_NON_INVERSIBLE);
	while (rt->n_objs > i && !exit_code)
	{
		exit_code = rt_update_transform(rt, &rt->objs[i], rt->objs[i].id);
		if (!exit_code)
			rt_set_material(rt->amb_intensity, &rt->objs[i], i % MATERIAL_MAX);
		++i;
	}
	return (exit_code);
}
