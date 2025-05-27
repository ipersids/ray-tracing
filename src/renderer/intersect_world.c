/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_world.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:05:03 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/26 21:30:25 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static void	quick_sort(t_intersection *arr, int low, int high);
static int	partition(t_intersection *arr, int low, int high);
static void	swap(t_intersection *t1, t_intersection *t2);

/* --------------------------- Public Functions ---------------------------- */

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
			xs.count = 0;// xs = intersect_plane(rt->objs[i].pl, *ray);
		if (ELEMENT_CYLINDER == rt->objs[i].id)
			xs.count = 0;// xs = intersect_cylinder(rt->objs[i].cy, *ray);
		if (0 < xs.count)
		{
			rt->ts[rt->n_ts].t = xs.t[0];
			rt->ts[rt->n_ts].i_object = i;
			++rt->n_ts;
			rt->ts[rt->n_ts].t = xs.t[1];
			rt->ts[rt->n_ts].i_object = i;
			++rt->n_ts;
		}
		++i;
	}
	quick_sort(rt->ts, 0, rt->n_ts - 1);
}

/* ------------------- Private Function Implementation --------------------- */

static void quick_sort(t_intersection *arr, int low, int high)
{
	int	i_pivot;

	if (low < high)
	{
		i_pivot = partition(arr, low, high);
		quick_sort(arr, low, i_pivot - 1);
		quick_sort(arr, i_pivot + 1, high);
	}
}

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

static void swap(t_intersection *t1, t_intersection *t2)
{
	t_intersection	tmp;

	tmp = *t1;
	t1->t = t2->t;
	t1->i_object = t2->i_object;
	t2->t = tmp.t;
	t2->i_object = tmp.i_object;
}
