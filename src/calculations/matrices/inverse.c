/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:12:30 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/20 15:44:07 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Attempts to compute the inverse of a matrix.
 * 
 * Calculates the inverse of matrix `m` and stores the result in `res`.
 * Returns false if the matrix is not invertible (determinant is zero).
 * 
 * @param m The matrix to invert.
 * @param res Pointer to store the resulting inverse matrix.
 * @return true if the matrix is invertible, false otherwise.
 */
bool	matrix_try_inverse(t_matrix m, t_matrix *res)
{
	float	det;
	size_t	row;
	size_t	col;

	det = matrix_determinant(m);
	if (equal(det, 0.0f))
		return (false);
	row = 0;
	while (m.dimension > row)
	{
		col = 0;
		while (m.dimension > col)
		{
			res->data[col][row] = matrix_cofactor(m, row, col) / det;
			++col;
		}
		++row;
	}
	res->dimension = m.dimension;
	return (true);
}

/**
 * @brief Calculates the determinant of a matrix.
 * 
 * @param m The matrix.
 * @return float The determinant value.
 */
float	matrix_determinant(t_matrix m)
{
	float	det;
	size_t	col;

	if (m.dimension == 0)
		return (1.0);
	if (m.dimension == 1)
		return (m.data[0][0]);
	if (m.dimension == 2)
		return (m.data[0][0] * m.data[1][1] - m.data[1][0] * m.data[0][1]);
	det = 0.0f;
	col = 0;
	while (m.dimension > col)
	{
		det += m.data[0][col] * matrix_cofactor(m, 0, col);
		++col;
	}
	return (det);
}

/**
 * @brief Calculates the cofactor of a matrix element.
 * 
 * The cofactor is the signed minor of the element at (row, col).
 * 
 * @param m The matrix.
 * @param row The row index.
 * @param col The column index.
 * @return float The cofactor value.
 */
float	matrix_cofactor(t_matrix m, size_t row, size_t col)
{
	float	res;

	res = matrix_minor(m, row, col);
	if ((col + row) % 2 == 0)
		return (res);
	return (-res);
}

/**
 * @brief Calculates the minor of a matrix element.
 * 
 * The minor is the determinant of the submatrix formed 
 * by removing the specified row and column.
 * 
 * @param m The matrix.
 * @param row The row to remove.
 * @param col The column to remove.
 * @return float The minor value.
 */
float	matrix_minor(t_matrix m, size_t row, size_t col)
{
	t_matrix	sub_m;

	sub_m = submatrix(m, row, col);
	return (matrix_determinant(sub_m));
}
