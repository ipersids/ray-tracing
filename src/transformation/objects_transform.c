/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_transform.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 00:10:38 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/07 15:57:55 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Sets up the transformation matrices for a sphere.
 *
 * @param sp Pointer to the sphere structure.
 * @return int 0 on success, or an error code if the matrix is not invertible.
 */
int	rt_sphere_transform(t_sphere *sp)
{
	t_matrix	translation;
	t_matrix	scaling;

	translation = matrix_translation(sp->pos.x, sp->pos.y, sp->pos.z);
	scaling = matrix_scaling(sp->scale, sp->scale, sp->scale);
	sp->transform = matrix_multiply(translation, scaling);
	sp->inv_transform = matrix_identity();
	if (false == matrix_try_inverse(sp->transform, &sp->inv_transform))
		return (ERR_MATRIX_NON_INVERSIBLE);
	sp->inv_transpose = matrix_transpose(sp->inv_transform);
	return (0);
}

/**
 * @brief Sets up the transformation matrices for a plane.
 *
 * @param pl Pointer to the plane structure.
 * @return int 0 on success, or an error code if the matrix is not invertible.
 */
int	rt_plane_transform(t_plane *pl)
{
	const t_vec3	canonical_normal = (t_vec3){0.0f, 1.0f, 0.0f};
	t_matrix		translation;
	t_matrix		rotation;

	translation = matrix_translation(pl->pos.x, pl->pos.y, pl->pos.z);
	rotation = matrix_rotation(canonical_normal, pl->dir);
	pl->transform = matrix_multiply(translation, rotation);
	pl->inv_transform = matrix_identity();
	if (false == matrix_try_inverse(pl->transform, &pl->inv_transform))
		return (ERR_MATRIX_NON_INVERSIBLE);
	pl->inv_transpose = matrix_transpose(pl->inv_transform);
	return (0);
}

/**
 * @brief Sets up the transformation matrices for a cylinder.
 *
 * @param cy Pointer to the cylinder structure.
 * @return int 0 on success, or an error code if the matrix is not invertible.
 */
int	rt_cylinder_transform(t_cylinder *cy)
{
	const t_vec3	canonical_normal = (t_vec3){0.0f, 1.0f, 0.0f};
	t_matrix		translation;
	t_matrix		rotation;
	t_matrix		scaling;

	translation = matrix_translation(cy->pos.x, cy->pos.y, cy->pos.z);
	rotation = matrix_rotation(canonical_normal, cy->dir);
	scaling = matrix_scaling(cy->scale, 1.0f, cy->scale);
	cy->transform = matrix_multiply(translation, rotation);
	cy->transform = matrix_multiply(cy->transform, scaling);
	cy->inv_transform = matrix_identity();
	if (false == matrix_try_inverse(cy->transform, &cy->inv_transform))
		return (ERR_MATRIX_NON_INVERSIBLE);
	cy->inv_transpose = matrix_transpose(cy->inv_transform);
	return (0);
}

/**
 * @brief Sets up the transformation matrices for a cone.
 *
 * @param co Pointer to the cone structure.
 * @return int 0 on success, or an error code if the matrix is not invertible.
 */
int	rt_cone_transform(t_cone *co)
{
	const t_vec3	canonical_normal = (t_vec3){0.0f, 1.0f, 0.0f};
	t_matrix		translation;
	t_matrix		rotation;
	t_matrix		transform;
	t_matrix		scaling;

	translation = matrix_translation(co->pos.x, co->pos.y, co->pos.z);
	scaling = matrix_scaling(co->scale, 1.0, co->scale);
	rotation = matrix_rotation(canonical_normal, co->dir);
	transform = matrix_multiply(translation, rotation);
	transform = matrix_multiply(transform, scaling);
	co->inv_transform = matrix_identity();
	if (false == matrix_try_inverse(transform, &co->inv_transform))
		return (ERR_MATRIX_NON_INVERSIBLE);
	co->inv_transpose = matrix_transpose(co->inv_transform);
	return (0);
}
