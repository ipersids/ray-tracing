#include "minirt.h"

float	find_closest_intersection(t_intersections hits)
{
	int		i;
	float	result;

	i = 0;
	result = -1;
	while (i < hits.count)
	{
		if (hits.t_values[i].t > 0.0)
		{
			if (result < 0 || hits.t_values[i].t < result)
				result = hits.t_values[i].t;
		}
		i++;
	}
	return (result);
}

// SHOULD IT BE ONE TRANSFORM FUNCTION THAT TAKES A POINTER TO A FUNCTION
// OR MULTIPLE ONES LIKE "SCALE RAY", "TRANSFORM RAY" etc.

t_ray	transform_ray(t_ray ray, t_matrix matrix)
{
	t_ray	result;

	result.orig = matrix_multiply_vec3(matrix, ray.orig);
	result.dir = matrix_multiply_vec3(matrix, ray.dir);
	return (result);
}
