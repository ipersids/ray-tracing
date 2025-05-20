/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_base_matrix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:48:53 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/20 15:36:33 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Creates an empty matrix (all elements set to 0.0f).
 * @return t_matrix The empty matrix.
 */
t_matrix	matrix_empty(void)
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

/**
 * @brief Creates an identity matrix.
 * @return t_matrix The identity matrix.
 */
t_matrix	matrix_identity(void)
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

/**
 * @brief Checks if two matrices are equal.
 * 
 * @param a First matrix.
 * @param b Second matrix.
 * @return true if matrices are equal, false otherwise.
 */
bool	matrix_equality(t_matrix a, t_matrix b)
{
	size_t	row;
	size_t	col;

	if (a.dimension != b.dimension)
		return (false);
	row = 0;
	while (a.dimension > row)
	{
		col = 0;
		while (a.dimension > col)
		{
			if (false == equal(a.data[row][col], b.data[row][col]))
				return (false);
			++col;
		}
		++row;
	}
	return (true);
}

/**
 * @brief Returns the transpose of a matrix.
 * 
 * @param self The matrix to transpose.
 * @return t_matrix The transposed matrix.
 */
t_matrix	matrix_transpose(t_matrix self)
{
	t_matrix	res;
	size_t		row;
	size_t		col;

	row = 0;
	while (self.dimension > row)
	{
		col = 0;
		while (self.dimension > col)
		{
			res.data[col][row] = self.data[row][col];
			++col;
		}
		++row;
	}
	res.dimension = self.dimension;
	return (res);
}
