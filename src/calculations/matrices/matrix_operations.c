/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 23:37:27 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/01 12:34:44 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Multiplies two matrices.
 *
 * Performs standard matrix multiplication between matrices a and b.
 * @warning If matrices have different dimensions, result is undefined.
 *
 * @param a First matrix.
 * @param b Second matrix.
 * @return t_matrix The result of a * b.
 */
t_matrix	matrix_multiply(t_matrix a, t_matrix b)
{
	size_t		row;
	size_t		col;
	t_matrix	res;

	row = 0;
	while (a.dimension > row && b.dimension > row)
	{
		col = 0;
		while (a.dimension > col && b.dimension > col)
		{
			res.data[row][col] = (
					a.data[row][0] * b.data[0][col]
					+ a.data[row][1] * b.data[1][col]
					+ a.data[row][2] * b.data[2][col]
					+ a.data[row][3] * b.data[3][col]
					);
			++col;
		}
		++row;
	}
	res.dimension = (size_t)ft_min(a.dimension, b.dimension);
	return (res);
}

/**
 * @brief Multiplies a matrix by a 3D point.
 *
 * Applies the transformation matrix m to the point p, 
 * including translation.
 *
 * @param m The transformation matrix.
 * @param p The point to transform.
 * @return t_vec3 The transformed point.
 */
t_vec3	matrix_multiply_point(t_matrix m, t_vec3 p)
{
	t_vec3	res;

	res.x = (
			m.data[0][0] * p.x + m.data[0][1] * p.y
			+ m.data[0][2] * p.z + m.data[0][3]
			);
	res.y = (
			m.data[1][0] * p.x + m.data[1][1] * p.y
			+ m.data[1][2] * p.z + m.data[1][3]
			);
	res.z = (
			m.data[2][0] * p.x + m.data[2][1] * p.y
			+ m.data[2][2] * p.z + m.data[2][3]
			);
	return (res);
}

/**
 * @brief Multiplies a matrix by a 3D vector.
 *
 * Applies the transformation matrix m to the vector v, 
 * ignoring translation.
 *
 * @param m The transformation matrix.
 * @param v The vector to transform.
 * @return t_vec3 The transformed vector.
 */
t_vec3	matrix_multiply_vector(t_matrix m, t_vec3 v)
{
	t_vec3	res;

	res.x = m.data[0][0] * v.x + m.data[0][1] * v.y + m.data[0][2] * v.z;
	res.y = m.data[1][0] * v.x + m.data[1][1] * v.y + m.data[1][2] * v.z;
	res.z = m.data[2][0] * v.x + m.data[2][1] * v.y + m.data[2][2] * v.z;
	return (res);
}
