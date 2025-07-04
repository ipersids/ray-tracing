/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reerikai <reerikai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:24:10 by reerikai          #+#    #+#             */
/*   Updated: 2025/06/23 14:24:11 by reerikai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pat	set_stripe_pattern_obj(void)
{
	const float	scale = 0.1;
	const float	angle_rad = 0.785398;
	t_pat		pattern;
	t_matrix	scale_matrix;
	t_matrix	rot_matrix;

	scale_matrix = matrix_scaling(scale, 1.0f, 1.0f);
	rot_matrix = matrix_rotation_y(angle_rad);
	pattern.type = PATTERN_STRIPE_OBJ;
	pattern.color_a = (t_color){0.0f, 0.0f, 0.f};
	pattern.color_b = (t_color){1.0f, 1.0f, 1.0f};
	pattern.has_pattern = true;
	pattern.transform = matrix_multiply(rot_matrix, scale_matrix);
	matrix_try_inverse(pattern.transform, &pattern.inv_transform);
	return (pattern);
}

t_pat	set_checker_pattern_obj(void)
{
	const float	scale = 0.5;
	t_pat		pattern;

	pattern.type = PATTERN_CHECKER_OBJ;
	pattern.color_a = (t_color){0.0f, 0.0f, 0.0f};
	pattern.color_b = (t_color){1.0f, 1.0f, 1.0f};
	pattern.has_pattern = true;
	pattern.transform = matrix_scaling(scale, scale, scale);
	matrix_try_inverse(pattern.transform, &pattern.inv_transform);
	return (pattern);
}

t_pat	set_ring_pattern_obj(void)
{
	const float	scale = 0.1;
	const float	angle_rad = 2.5;
	t_pat		pattern;
	t_matrix	scale_matrix;
	t_matrix	rot_matrix;

	scale_matrix = matrix_scaling(scale, 1.0f, 1.0f);
	rot_matrix = matrix_rotation_y(angle_rad);
	pattern.type = PATTERN_RING_OBJ;
	pattern.color_a = (t_color){0.0f, 0.0f, 0.0f};
	pattern.color_b = (t_color){1.0f, 1.0f, 1.0f};
	pattern.has_pattern = true;
	pattern.transform = matrix_multiply(rot_matrix, scale_matrix);
	matrix_try_inverse(pattern.transform, &pattern.inv_transform);
	return (pattern);
}
