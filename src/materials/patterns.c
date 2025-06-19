#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

// t_pat	set_stripe_pattern(t_color a, t_color b, float scale, float angle_rad)
t_pat	set_stripe_pattern(void)
{
	const float	scale = 10;
	const float angle_rad = 0.785398;
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

// t_pat	set_checker_pattern(t_color a, t_color b, float scale)
t_pat	set_checker_pattern(void)
{
	const float	scale = 10;
	t_pat		pattern;

	pattern.type = PATTERN_CHECKER;
	pattern.color_a = (t_color){0.0f, 0.0f, 0.f};
	pattern.color_b = (t_color){1.0f, 1.0f, 1.0f};
	pattern.has_pattern = true;
	pattern.transform = matrix_scaling(scale, scale, scale);
	matrix_try_inverse(pattern.transform, &pattern.inv_transform);
	return (pattern);
}

// t_pat	set_gradient_pattern(t_color a, t_color b, float scale)
t_pat	set_gradient_pattern(void)
{
	const float	scale = 10;
	t_pat		pattern;

	pattern.type = PATTERN_GRADIENT;
	pattern.color_a = (t_color){0.0f, 0.0f, 0.f};
	pattern.color_b = (t_color){1.0f, 1.0f, 1.0f};
	pattern.has_pattern = true;
	pattern.transform = matrix_scaling(scale, 1.0f, 1.0f);
	matrix_try_inverse(pattern.transform, &pattern.inv_transform);
	return (pattern);
}
