/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_at.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:12:23 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/01 13:15:52 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Computes the normal vector at a given point on an object's surface.
 *
 * @param obj Pointer to the object.
 * @param world_point The point in world coordinates where the normal is calculated.
 * @return t_vec3 The normal vector at the given point.
 */
t_vec3	normal_at(t_object *obj, t_point world_point)
{
	// if (ELEMENT_SPHERE == obj->id)
	// 	return (sphere_normal_at(&obj->sp, world_point));
	if (ELEMENT_PLANE == obj->id)
		return (plane_normal_at(&obj->pl));
	// if (ELEMENT_CYLINDER == obj->id)
	// 	return (cylinder_normal_at(&obj->cy, world_point));
	return (sphere_normal_at(&obj->sp, world_point));
}
