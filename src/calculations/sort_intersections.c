/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_intersections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:25:14 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/07 16:26:41 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	partition(t_intersection *arr, int low, int high);
static void	swap(t_intersection *t1, t_intersection *t2);

/**
 * @brief Sorts an array of intersections using quick sort.
 *
 * @param arr Array of intersections.
 * @param low Lower index.
 * @param high Higher index.
 */
void	intersections_sort(t_intersection *arr, int low, int high)
{
	int	i_pivot;

	if (low < high)
	{
		i_pivot = partition(arr, low, high);
		intersections_sort(arr, low, i_pivot - 1);
		intersections_sort(arr, i_pivot + 1, high);
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
