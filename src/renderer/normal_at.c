/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_at.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:12:23 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/21 11:40:19 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

t_vec3	bumped_normal_at(t_info *rt, t_object *obj, t_point *p, t_type id);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Computes the normal vector at a given point on an object's surface.
 *
 * @param obj Pointer to the object.
 * @param world_point Point in world coordinates where the normal is calculated.
 * @return t_vec3 The normal vector at the given point.
 */
t_vec3	rt_normal_at(t_info *rt, t_object *obj, t_point p, t_type id)
{
	if (IS_BONUS && obj->has_bump_map)
		return (bumped_normal_at(rt, obj, &p, id));
	if (ELEMENT_SPHERE == id)
		return (sphere_normal_at(&obj->sp, p));
	if (ELEMENT_PLANE == id)
		return (rt_plane_normal_at(&obj->pl));
	if (ELEMENT_CYLINDER == id)
		return (rt_cylinder_normal_at(&obj->cy, p));
	if (ELEMENT_CYLINDER_CAP == id)
		return (rt_cylinder_cap_normal_at(&obj->cy, p));
	if (ELEMENT_CONE == id)
		return (rt_cone_normal_at(&obj->co, p));
	if (ELEMENT_CONE_CAP == id)
		return (rt_cone_cap_normal_at(&obj->co));
	else
		rt_destroy_exit(rt, ERR_OBJECT_TYPE);
	return (sphere_normal_at(&obj->sp, p));
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Computes the bumped (perturbed) normal at a point using a bump map.
 *
 * @param rt Pointer to the main program structure.
 * @param obj Pointer to the object.
 * @param p Pointer to the point in world coordinates.
 * @param id The type of the object.
 * @return The bumped normal vector at the given point.
 */
t_vec3	bumped_normal_at(t_info *rt, t_object *obj, t_point *p, t_type id)
{
	mlx_image_t	*bump_map;

	bump_map = rt->win.bump_map[obj->bump_type];
	if (ELEMENT_SPHERE == id)
		return (rt_sphere_bumped_normal_at(bump_map, &obj->sp, p));
	if (ELEMENT_PLANE == id)
		return (rt_plane_bumped_normal_at(bump_map, &obj->pl, p));
	if (ELEMENT_CYLINDER == id)
		return (rt_cylinder_bumped_normal_at(bump_map, &obj->cy, p));
	if (ELEMENT_CYLINDER_CAP == id)
		return (rt_cap_bumped_normal_at(bump_map, &obj->cy, p));
	if (ELEMENT_CONE == id)
		return (rt_cone_bumped_normal_at(bump_map, &obj->co, p));
	if (ELEMENT_CONE_CAP == id)
		return (rt_cone_cap_bumped_normal_at(bump_map, &obj->co, p));
	else
		rt_destroy_exit(rt, ERR_OBJECT_TYPE);
	return (rt_sphere_bumped_normal_at(bump_map, &obj->sp, p));
}
