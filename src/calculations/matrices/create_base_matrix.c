/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_base_matrix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:48:53 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/19 16:20:28 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_matrix.h"

t_matrix	empty(void)
{
	t_matrix	res;
	size_t		row;
	size_t		col;

	row = 0;
	res.dimension = M_SIZE;
	while (M_SIZE > row)
	{
		col = 0;
		while (M_SIZE > col)
		{
			res.data[row][col] = 0.0f;
			++col;
		}
		++row;
	}
	return (res);
}

t_matrix	identity(void)
{
	t_matrix	res;
	size_t		row;
	size_t		col;

	row = 0;
	res.dimension = M_SIZE;
	while (M_SIZE > row)
	{
		col = 0;
		while (M_SIZE > col)
		{
			if (col != row)
				res.data[row][col] = 0.0f;
			else
				res.data[row][col] = 1.0f;
			++col;
		}
		++row;
	}
	return (res);
}

