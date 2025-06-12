
#include "minirt.h"

static void	find_object(t_object object, t_matrix *obj_inv);

t_color	pattern_at_object(t_pat pattern, t_object obj, t_point w_point)
{
	t_point		object_point;
	t_point		pattern_point;
	t_matrix	obj_inv;

	find_object(obj, &obj_inv);
	object_point = matrix_multiply_vector(obj_inv, w_point);
	pattern_point = matrix_multiply_vector(pattern.inv_transform, object_point);
	if (pattern.type == PATTERN_STRIPE)
		return (stripe_pattern_at(pattern, pattern_point));
	else if (pattern.type == PATTERN_GRADIENT)
		return (gradient_pattern_at(pattern, pattern_point));
	// else if (pattern.type == PATTERN_RING)
	// 	return (ring_pattern_at(pattern, pattern_point));
	else if (pattern.type == PATTERN_CHECKER)
		return (checker_pattern_at(pattern, pattern_point));
	// else if (pattern.type == PATTERN_RADIANT_GRADIENT)
	// 	return (radiant_gradient_pattern_at(pattern, pattern_point));
	return (BLACK);
}

t_color	stripe_pattern_at(t_pat pattern, t_point point)
{
	if ((int)floorf(point.x) % 2 == 0)
		return (pattern.color_a);
	else
		return (pattern.color_b);
}

t_color	gradient_pattern_at(t_pat pattern, t_point point)
{
	t_color	distance;
	float	fraction;

	distance = subtraction(pattern.color_b, pattern.color_a);
	//fraction = fabsf(point.x) - floorf(fabsf(point.x));
	fraction = point.x - floor(point.x);
	//printf("Gradient at x=%.2f -> %.2f\n", point.z, fraction);
	return (addition(pattern.color_a, (multiply_color_scalar(distance, fraction))));
}

// t_color	ring_pattern_at(t_pat pattern, t_point point)
// {
// 	float	distance;

// 	distance = sqrtf(point.x * point.x + point.z * point.z);
// 	if ((int)floorf(distance) % 2 == 0)
// 		return (pattern.color_a);
// 	else
// 		return (pattern.color_b);
// }

t_color	checker_pattern_at(t_pat pattern, t_point point)
{
	int sum = (int)(floorf(point.x + PATTERN_SHIFT) +
	                floorf(point.y + PATTERN_SHIFT) +
	                floorf(point.z + PATTERN_SHIFT));
	if (sum % 2 == 0)
		return (pattern.color_a);
	return (pattern.color_b);
}


// t_color	radiant_gradient_pattern_at(t_pat pattern, t_point point)
// {
// 	float	fraction;
// 	float	distance;
// 	t_color	col_distance;

// 	distance = sqrtf(point.x * point.x + point.z * point.z);
// 	fraction = distance - floorf(distance);
// 	col_distance = subtraction(pattern.color_b, pattern.color_a);
// 	return (addition(pattern.color_a, (multiply_color_scalar(col_distance, fraction))));
// }

static void	find_object(t_object object, t_matrix *obj_inv)
{
	if (object.id == ELEMENT_SPHERE)
		*obj_inv = object.sp.inv_transform;
	else if (object.id == ELEMENT_PLANE)
		*obj_inv = object.pl.inv_transform;
	else if (object.id == ELEMENT_CYLINDER)
		*obj_inv = object.cy.inv_transform;
	else
		*obj_inv = matrix_identity();
}
