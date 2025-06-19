/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_world.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:05:03 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/20 00:26:48 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static t_intersections	handle_bonus_shape(t_ray *ray, t_info *rt, size_t i);

/**
 * @brief Adds all intersections from xs to the global intersection array.
 *
 * @param xs Pointer to the intersections structure.
 * @param rt Pointer to the main program structure.
 * @param i Index of the object being intersected.
 */
static void				add_intersections(const t_intersections *xs,
							t_info *rt, size_t i);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Intersects a ray with all objects in the world.
 *
 * Iterates through all objects in the scene, computes intersections 
 * with the given ray, and stores all intersections in the rt->ts array. 
 * After collecting intersections, sorts them by distance using quick sort.
 *
 * @param rt Pointer to the main program structure.
 * @param ray Pointer to the ray to test for intersections.
 */
void	rt_intersect_world(t_info *rt, t_ray *ray)
{
	size_t			i;
	t_intersections	xs;

	i = 0;
	rt->n_ts = 0;
	while (i < rt->n_objs)
	{
		if (ELEMENT_SPHERE == rt->objs[i].id)
			xs = intersect_sphere(rt->objs[i].sp, *ray);
		else if (ELEMENT_PLANE == rt->objs[i].id)
			xs = rt_intersect_plane(&rt->objs[i].pl, *ray);
		else if (ELEMENT_CYLINDER == rt->objs[i].id)
		{
			xs = rt_intersect_cylinder(&rt->objs[i].cy, *ray);
			add_intersections(&xs, rt, i);
			xs = rt_intersect_cylinder_cap(&rt->objs[i].cy, *ray);
		}
		else if (IS_BONUS)
			xs = handle_bonus_shape(ray, rt, i);
		add_intersections(&xs, rt, i);
		++i;
	}
	intersections_sort(rt->ts, 0, rt->n_ts - 1);
}

/* ------------------- Private Function Implementation --------------------- */

static t_intersections	handle_bonus_shape(t_ray *ray, t_info *rt, size_t i)
{
	t_intersections	xs;

	xs.count = 0;
	if (ELEMENT_CONE == rt->objs[i].id)
	{
		xs = rt_intersect_cone(&rt->objs[i].co, *ray);
		add_intersections(&xs, rt, i);
		xs = rt_intersect_cone_cap(&rt->objs[i].co, *ray);
	}
	return (xs);
}

static void	add_intersections(const t_intersections *xs, t_info *rt, size_t i)
{
	size_t			j;
	t_intersection	*tmp;
	size_t			nsize;

	j = 0;
	tmp = NULL;
	if (0 >= xs->count)
		return ;
	if ((rt->n_ts + xs->count) >= rt->capacity_ts)
	{
		nsize = ((rt->capacity_ts + xs->count) * 2) * sizeof(t_intersection);
		tmp = ft_realloc(rt->ts, rt->capacity_ts, nsize);
		if (!tmp)
			rt_destroy_exit(rt, ERR_REALLOC_INTERSECTIONS);
		rt->ts = tmp;
		rt->capacity_ts = (rt->capacity_ts + xs->count) * 2;
	}
	while (j < xs->count)
	{
		rt->ts[rt->n_ts].t = xs->t[j];
		rt->ts[rt->n_ts].i_object = i;
		rt->ts[rt->n_ts].obj_type = xs->obj_type;
		++rt->n_ts;
		++j;
	}
}
