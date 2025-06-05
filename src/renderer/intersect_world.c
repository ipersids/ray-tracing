/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_world.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:05:03 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/06 01:26:03 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

/**
 * @brief Sorts an array of intersections using quick sort.
 *
 * @param arr Array of intersections.
 * @param low Lower index.
 * @param high Higher index.
 */
static void	quick_sort(t_intersection *arr, int low, int high);
static int	partition(t_intersection *arr, int low, int high);
static void	swap(t_intersection *t1, t_intersection *t2);

/**
 * @brief Adds all intersections from xs to the global intersection array.
 *
 * @param xs Pointer to the intersections structure.
 * @param rt Pointer to the main program structure.
 * @param i Index of the object being intersected.
 */
static void	add_intersections(const t_intersections *xs, t_info *rt, size_t i);

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
		if (ELEMENT_PLANE == rt->objs[i].id)
			xs = rt_intersect_plane(&rt->objs[i].pl, *ray);
		if (ELEMENT_CYLINDER == rt->objs[i].id)
		{
			xs = rt_intersect_cylinder(&rt->objs[i].cy, *ray);
			add_intersections(&xs, rt, i);
			xs = rt_intersect_cap(&rt->objs[i].cy, *ray);
		}
		add_intersections(&xs, rt, i);
		++i;
	}
	quick_sort(rt->ts, 0, rt->n_ts - 1);
}

/* ------------------- Private Function Implementation --------------------- */

static void	quick_sort(t_intersection *arr, int low, int high)
{
	int	i_pivot;

	if (low < high)
	{
		i_pivot = partition(arr, low, high);
		quick_sort(arr, low, i_pivot - 1);
		quick_sort(arr, i_pivot + 1, high);
	}
}

/**
 * @brief Partitions the array for quick sort.
 *
 * @param arr Array of intersections.
 * @param low Lower index.
 * @param high Higher index.
 * @return int The partition index.
 */
static int	partition(t_intersection *arr, int low, int high)
{
	t_intersection	pivot;
	int				i;
	int				j;

	pivot = arr[high];
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (arr[j].t <= pivot.t)
		{
			++i;
			swap(&arr[i], &arr[j]);
		}
		++j;
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

/**
 * @brief Swaps two intersection structures.
 *
 * @param t1 Pointer to the first intersection.
 * @param t2 Pointer to the second intersection.
 */
static void	swap(t_intersection *t1, t_intersection *t2)
{
	t_intersection	tmp;

	tmp = *t1;
	t1->t = t2->t;
	t1->i_object = t2->i_object;
	t1->obj_type = t2->obj_type;
	t2->t = tmp.t;
	t2->i_object = tmp.i_object;
	t2->obj_type = tmp.obj_type;
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
			rt_destroy_exit(rt, ERROR_REALLOC_INTERSECTIONS);
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
