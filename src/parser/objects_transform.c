/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_transform.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 00:10:38 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/26 10:59:14 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	sphere_transform(t_sphere *sp);
static int	plane_transform(t_plane *pl);
static int	cylinder_transform(t_cylinder *cy);

int	rt_set_transformations(t_info *rt)
{
	size_t	i;
	int		exit_code;

	i = 0;
	exit_code = 0;
	while (rt->n_objs > i && 0 == exit_code)
	{
		if (ELEMENT_SPHERE == rt->objs[i].id)
			exit_code = sphere_transform(&rt->objs[i].sp);
		else if (ELEMENT_PLANE == rt->objs[i].id)
			exit_code = plane_transform(&rt->objs[i].pl);
		else if (ELEMENT_CYLINDER == rt->objs[i].id)
			exit_code = cylinder_transform(&rt->objs[i].cy);
		else
			exit_code = ERR_OBJECT_TYPE;
		++i;
	}
	return (exit_code);
}

static int	sphere_transform(t_sphere *sp)
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

static int	plane_transform(t_plane *pl)
{
	(void)pl;
	return (0);
}

static int	cylinder_transform(t_cylinder *cy)
{
	(void)cy;
	return (0);
}
