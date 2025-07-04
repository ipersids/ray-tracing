/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reerikai <reerikai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:23:58 by reerikai          #+#    #+#             */
/*   Updated: 2025/06/23 14:23:59 by reerikai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

t_pat	set_stripe_pattern(void)
{
	const float	scale = 10;
	const float	angle_rad = 0.785398;
	t_pat		pattern;
	t_matrix	scale_matrix;
	t_matrix	rot_matrix;

	scale_matrix = matrix_scaling(scale, 1.0f, 1.0f);
	rot_matrix = matrix_rotation_y(angle_rad);
	pattern.type = PATTERN_STRIPE;
	pattern.color_a = (t_color){0.0f, 0.0f, 0.f};
	pattern.color_b = (t_color){1.0f, 1.0f, 1.0f};
	pattern.has_pattern = true;
	pattern.transform = matrix_multiply(rot_matrix, scale_matrix);
	matrix_try_inverse(pattern.transform, &pattern.inv_transform);
	return (pattern);
}

t_pat	set_checker_pattern(void)
{
	const float	scale = 10;
	t_pat		pattern;

	pattern.type = PATTERN_CHECKER;
	pattern.color_a = (t_color){0.0f, 0.0f, 0.0f};
	pattern.color_b = (t_color){1.0f, 1.0f, 1.0f};
	pattern.has_pattern = true;
	pattern.transform = matrix_scaling(scale, scale, scale);
	matrix_try_inverse(pattern.transform, &pattern.inv_transform);
	return (pattern);
}

t_pat	set_gradient_pattern(void)
{
	const float	scale = 10;
	t_pat		pattern;

	pattern.type = PATTERN_GRADIENT;
	pattern.color_a = (t_color){0.0f, 0.0f, 0.0f};
	pattern.color_b = (t_color){1.0f, 1.0f, 1.0f};
	pattern.has_pattern = true;
	pattern.transform = matrix_scaling(scale, 1.0f, 1.0f);
	matrix_try_inverse(pattern.transform, &pattern.inv_transform);
	return (pattern);
}

t_pat	set_ring_pattern(void)
{
	const float	scale = 1.0;
	t_pat		pattern;

	pattern.type = PATTERN_RING;
	pattern.color_a = (t_color){0.0f, 0.0f, 0.0f};
	pattern.color_b = (t_color){1.0f, 1.0f, 1.0f};
	pattern.has_pattern = true;
	pattern.transform = matrix_scaling(scale, 1.0f, 1.0f);
	matrix_try_inverse(pattern.transform, &pattern.inv_transform);
	return (pattern);
}

t_color	ring_pattern_at(t_pat pattern, t_point point)
{
	float	distance;

	distance = sqrtf(point.x * point.x + point.z * point.z);
	if ((int)floorf(distance) % 2 == 0)
		return (pattern.color_a);
	else
		return (pattern.color_b);
}
