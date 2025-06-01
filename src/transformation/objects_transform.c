/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_transform.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 00:10:38 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/01 11:07:41 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_sphere_transform(t_sphere *sp)
{
	t_matrix	translation;
	t_matrix	scaling;
	
	translation = matrix_translation(sp->pos.x, sp->pos.y, sp->pos.z);
	scaling = matrix_scaling(sp->r, sp->r, sp->r);
	sp->transform = matrix_multiply(translation, scaling);   
	sp->inv_transform = matrix_identity();
	if (false == matrix_try_inverse(sp->transform, &sp->inv_transform))
		return (ERR_MATRIX_NON_INVERSIBLE);
	sp->inv_transpose = matrix_transpose(sp->inv_transform);   
	sp->scale = sp->r;
	sp->r = 1.0;
	return (0);
}

int	rt_plane_transform(t_plane *pl)
{
	const t_vec3	canonical_normal = (t_vec3){0.0f, 1.0f, 0.0f};
	t_matrix		translation;
	t_matrix		rotation;

	translation = matrix_translation(pl->pos.x, pl->pos.y, pl->pos.z);
	rotation = matrix_rotation(pl->dir, canonical_normal);
	pl->transform = matrix_multiply(translation, rotation);
	pl->inv_transform = matrix_identity();
	if (false == matrix_try_inverse(pl->transform, &pl->inv_transform))
		return (ERR_MATRIX_NON_INVERSIBLE);
	pl->inv_transpose = matrix_transpose(pl->inv_transform);
	pl->dir = normalize(pl->dir);
	return (0);
}

int	rt_cylinder_transform(t_cylinder *cy)
{
	(void)cy;
	return (0);
}
