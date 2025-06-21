/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 00:23:17 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/21 12:09:43 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Wrapper to update the transformation matrices for a scene obj/camera.
 * @param rt Pointer to the main program structure.
 * @param obj Pointer to the object to update.
 * @param id The type of the object (ELEMENT_SPHERE, ELEMENT_PLANE, etc.).
 * @return 0 on success, or an error code if the object type is unknown 
 * 		   or transformation fails.
 */
int	rt_update_transform(t_info *rt, void *obj, t_type id)
{
	t_object	*shape;
	int			exit_code;

	if (ELEMENT_CAMERA == id)
		return (rt_view_transform(&rt->camera, rt->win.world_up));
	shape = (t_object *)obj;
	exit_code = 0;
	if (ELEMENT_SPHERE == id)
		exit_code = rt_sphere_transform(&(shape->sp));
	else if (ELEMENT_PLANE == id)
		exit_code = rt_plane_transform(&(shape->pl));
	else if (ELEMENT_CYLINDER == id)
		exit_code = rt_cylinder_transform(&(shape->cy));
	else if (IS_BONUS && ELEMENT_CONE == id)
		exit_code = rt_cone_transform(&(shape->co));
	else if (ELEMENT_UNKNOWN <= id)
		exit_code = ERR_OBJECT_TYPE;
	return (exit_code);
}
