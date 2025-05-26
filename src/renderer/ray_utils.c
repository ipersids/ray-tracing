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

t_ray	transform_ray(t_ray ray, t_matrix matrix)
{
	t_ray	result;

	result.orig = matrix_multiply_vec3(matrix, ray.orig);
	result.dir = matrix_multiply_vec3(matrix, ray.dir);
	return (result);
}

//			THIS WILL BE NEEDED LATER

// t_vec3	normal_at(t_sphere sphere, t_point world_point)
// {
// 	t_vec3		object_point;
// 	t_vec3		object_normal;
// 	t_vec3		world_normal;
// 	t_matrix	inv;
// 	t_matrix	inv_transpose;

// 	inv = inverse(sphere.transform);
// 	object_point = matrix_multiply_vec3(inv, world_point);
// 	object_normal = subtraction(object_point, (t_point){0, 0, 0});
// 	inv_transpose = matrix_transpose(inv);
// 	world_normal = matrix_multiply_vec3(inv_transpose, object_normal);
// 	world_normal = normalize(world_normal);
// 	return(world_normal);
// }

//			THIS WILL BE NEEDED LATER

// t_vec3	reflect(t_vec3 in, t_vec3 normal)
// {
// 	t_vec3	result;
// 	t_vec3	scaled_norm;

// 	scaled_norm = multiplication(normal, 2 * dot_product(in, normal));
// 	result = subtraction(in, scaled_norm);
// 	return (result);
// }
