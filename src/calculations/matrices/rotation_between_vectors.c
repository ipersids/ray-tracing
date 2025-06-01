/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_between_vectors.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 23:59:25 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/01 12:45:54 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

/**
 * @brief Returns a rotation matrix for a given axis and angle. 
 * 
 * Uses Rodrigues' formula: 
 * https://mathworld.wolfram.com/RodriguesRotationFormula.html
 *
 * @param axis The axis to rotate around (should be normalized).
 * @param angle The angle in radians.
 * @return t_matrix The rotation matrix.
 */
static t_matrix	get_rotation(t_vec3 axis, float angle);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Computes the rotation matrix to rotate one vector to another.
 *
 * Given two normalized vectors, returns a rotation matrix that rotates
 * from_norm to to_norm. Handles the cases where the vectors are already
 * aligned or exactly opposite.
 *
 * @param from_norm The starting normalized vector.
 * @param to_norm The target normalized vector.
 * @return t_matrix The rotation matrix.
 */
t_matrix	matrix_rotation(t_vec3 from_norm, t_vec3 to_norm)
{
	const float	strict_epsilon = 1e-10;
	t_vec3		perpendicular;
	t_vec3		axis;
	float		angle;

	if (magnitude(subtraction(from_norm, to_norm)) < strict_epsilon)
		return (matrix_identity());
	if (magnitude(addition(from_norm, to_norm)) < strict_epsilon)
	{
		perpendicular = (t_vec3){0.0f, 1.0f, 0.0f};
		if (fabsf(from_norm.x) < 0.9f)
			perpendicular = (t_vec3){1.0f, 0.0f, 0.0f};
		axis = cross_product(from_norm, perpendicular);
		return (get_rotation(axis, M_PI));
	}
	axis = cross_product(from_norm, to_norm);
	if (magnitude(axis) < strict_epsilon)
		return (matrix_identity());
	angle = acos(dot_product(from_norm, to_norm));
	axis = normalize(axis);
	return (get_rotation(axis, angle));
}

/* ------------------- Private Function Implementation --------------------- */

static t_matrix	get_rotation(t_vec3 axis, float angle)
{
	float		cos_theta;
	float		sin_theta;
	float		one_minus_cos;
	t_matrix	rotation;

	rotation = matrix_identity();
	cos_theta = cosf(angle);
	one_minus_cos = 1.0f - cos_theta;
	sin_theta = sinf(angle);
	rotation.data[0][0] = cos_theta + axis.x * axis.x * one_minus_cos;
	rotation.data[0][1] = axis.x * axis.y * one_minus_cos - axis.z * sin_theta;
	rotation.data[0][2] = axis.x * axis.z * one_minus_cos + axis.y * sin_theta;
	rotation.data[1][0] = axis.y * axis.x * one_minus_cos + axis.z * sin_theta;
	rotation.data[1][1] = cos_theta + axis.y * axis.y * one_minus_cos;
	rotation.data[1][2] = axis.y * axis.z * one_minus_cos - axis.x * sin_theta;
	rotation.data[2][0] = axis.z * axis.x * one_minus_cos - axis.y * sin_theta;
	rotation.data[2][1] = axis.z * axis.y * one_minus_cos + axis.x * sin_theta;
	rotation.data[2][2] = cos_theta + axis.z * axis.z * one_minus_cos;
	return (rotation);
}
