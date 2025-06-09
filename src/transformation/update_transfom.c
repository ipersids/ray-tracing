/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_transfom.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:28:48 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/09 13:10:39 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

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
	else if (ELEMENT_UKNOWN <= id)
		exit_code = ERR_OBJECT_TYPE;
	return (exit_code);
}
