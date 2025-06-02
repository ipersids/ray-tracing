/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_transformations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:51:04 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/02 13:53:59 by ipersids         ###   ########.fr       */
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
	if (0 != rt_view_transform(&rt->camera, rt->win.world_up))
		return (ERR_CAMERA_GIMBAL_LOCK);
	while (rt->n_objs > i && 0 == exit_code)
	{
		if (ELEMENT_SPHERE == rt->objs[i].id)
			exit_code = rt_sphere_transform(&rt->objs[i].sp);
		else if (ELEMENT_PLANE == rt->objs[i].id)
			exit_code = rt_plane_transform(&rt->objs[i].pl);
		else if (ELEMENT_CYLINDER == rt->objs[i].id)
			exit_code = rt_cylinder_transform(&rt->objs[i].cy);
		else
			exit_code = ERR_OBJECT_TYPE;
		rt_set_material(rt->ambient.intensity, &rt->objs[i], i % MATERIAL_MAX);
		++i;
	}
	return (exit_code);
}
