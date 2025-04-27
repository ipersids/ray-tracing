/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:05:25 by ipersids          #+#    #+#             */
/*   Updated: 2025/04/20 13:51:33 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Frees a dynamically allocated array of strings.
 * 
 * @param arr Pointer to the array of strings to be freed.
 * @param i The number of elements in the array.
 */
void	rt_free_arr(void **arr, int i)
{
	int	j;

	j = 0;
	if (!arr)
		return ;
	while (j < i || NULL != arr[j])
	{
		free(arr[j]);
		arr[j] = NULL;
		j++;
	}
	free(arr);
	arr = NULL;
}
