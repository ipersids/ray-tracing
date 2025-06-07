/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_at.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:12:23 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/07 03:27:03 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Computes the normal vector at a given point on an object's surface.
 *
 * @param obj Pointer to the object.
 * @param world_point Point in world coordinates where the normal is calculated.
 * @return t_vec3 The normal vector at the given point.
 */
t_vec3	rt_normal_at(t_object *obj, t_point world_point, t_type otype)
{
	if (ELEMENT_PLANE == otype)
		return (rt_plane_normal_at(&obj->pl));
	if (ELEMENT_CYLINDER == otype)
		return (rt_cylinder_normal_at(&obj->cy, world_point));
	if (ELEMENT_CYLINDER_CAP == otype)
		return (rt_cap_normal_at(&obj->cy, world_point));
	if (ELEMENT_CONE == otype)
		return (rt_cone_normal_at(&obj->co, world_point));
	return (sphere_normal_at(&obj->sp, world_point));
}
