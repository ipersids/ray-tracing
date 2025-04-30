/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_free_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:05:25 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/01 01:21:08 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Frees a dynamically allocated array of pointers.
 * 
 * If the array is null-terminated, the function calculates 
 * the number of elements.
 * 
 * @param arr Pointer to the array of pointers to be freed.
 * @param i The number of elements in the array, 
 * 			or NULL_TERMINATED_ARR if the array is null-terminated.
 */
void	rt_free_arr(void **arr, int i)
{
	int	j;

	j = 0;
	if (!arr)
		return ;
	if (i == NULL_TERMINATED_ARR)
	{
		i = 0;
		while (NULL != arr[i])
			i++;
	}
	while (j < i || NULL != arr[j])
	{
		free(arr[j]);
		arr[j] = NULL;
		j++;
	}
	free(arr);
	arr = NULL;
}
