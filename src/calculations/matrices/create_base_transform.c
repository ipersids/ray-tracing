/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_base_transform.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:29:30 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/20 15:48:11 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Creates a translation matrix.
 * 
 * Translation moves a point by (x, y, z).  
 * 
 * @warning Translation does not affect vectors! Applying translation 
 * 			to a vec3 causes undefined behaviour.
 * 
 * @param x Translation along the x-axis.
 * @param y Translation along the y-axis.
 * @param z Translation along the z-axis.
 * @return t_matrix The translation matrix.
 */
t_matrix	matrix_translation(float x, float y, float z)
{
	t_matrix	res;

	res = matrix_identity();
	res.data[0][3] = x;
	res.data[1][3] = y;
	res.data[2][3] = z;
	return (res);
}

/**
 * @brief Creates a scaling matrix.
 * 
 * Scales a point or vector by (x, y, z).
 * 
 * @param x Scaling factor along the x-axis.
 * @param y Scaling factor along the y-axis.
 * @param z Scaling factor along the z-axis.
 * @return t_matrix The scaling matrix.
 */
t_matrix	matrix_scaling(float x, float y, float z)
{
	t_matrix	res;

	res = matrix_identity();
	res.data[0][0] = x;
	res.data[1][1] = y;
	res.data[2][2] = z;
	return (res);
}

/**
 * @brief Creates a rotation matrix around the X axis.
 * 
 * Rotates a point or vector by the given angle 
 * in radians around the X axis.
 * 
 * @param radians Angle in radians.
 * @return t_matrix The rotation matrix.
 */
t_matrix	matrix_rotation_x(float radians)
{
	t_matrix	res;

	res = matrix_identity();
	res.data[1][1] = cos(radians);
	res.data[1][2] = -sin(radians);
	res.data[2][1] = sin(radians);
	res.data[2][2] = cos(radians);
	return (res);
}

/**
 * @brief Creates a rotation matrix around the Y axis.
 * 
 * Rotates a point or vector by the given angle 
 * in radians around the Y axis.
 * 
 * @param radians Angle in radians.
 * @return t_matrix The rotation matrix.
 */
t_matrix	matrix_rotation_y(float radians)
{
	t_matrix	res;

	res = matrix_identity();
	res.data[0][0] = cos(radians);
	res.data[0][2] = sin(radians);
	res.data[2][0] = -sin(radians);
	res.data[2][2] = cos(radians);
	return (res);
}

/**
 * @brief Creates a rotation matrix around the Z axis.
 * 
 * Rotates a point or vector by the given angle 
 * in radians around the Z axis.
 * 
 * @param radians Angle in radians.
 * @return t_matrix The rotation matrix.
 */
t_matrix	matrix_rotation_z(float radians)
{
	t_matrix	res;

	res = matrix_identity();
	res.data[0][0] = cos(radians);
	res.data[0][1] = -sin(radians);
	res.data[1][0] = sin(radians);
	res.data[1][1] = cos(radians);
	return (res);
}
