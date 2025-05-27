#include "minirt.h"

t_intersection	*find_closest_intersection(t_intersection *ts, int n_ts)
{
	int	i;

	if (n_ts <= 0)
		return (NULL);
	i = 0;
	while (i < n_ts)
	{
		if (ts[i].t >= 0.0f)
			return (&ts[i]);
		++i;
	}
	return (NULL);
}

t_ray	transform_ray(t_ray ray, t_matrix matrix)
{
	t_ray	result;

	result.orig = matrix_multiply_vec3(matrix, ray.orig);
	result.dir = matrix_multiply_vec3(matrix, ray.dir);
	return (result);
}

t_vec3	normal_at(t_object *obj, t_point world_point)
{
	// if (ELEMENT_SPHERE == obj->id)
	// 	return (sphere_normal_at(&obj->sp, world_point));
	// if (ELEMENT_PLANE == obj->id)
	// 	return (plane_normal_at(&obj->pl, world_point));
	// if (ELEMENT_CYLINDER == obj->id)
	// 	return (cylinder_normal_at(&obj->cy, world_point));
	return (sphere_normal_at(&obj->sp, world_point));
}

t_vec3	sphere_normal_at(t_sphere *sp, t_point world_point)
{
	t_vec3		obj_point;
	t_vec3		obj_normal;
	t_vec3		world_normal;

	obj_point = matrix_multiply_vec3(sp->inv_transform, world_point);
	obj_normal = subtraction(obj_point, sp->center);
	world_normal = matrix_multiply_vec3(sp->inv_transpose, obj_normal);
	world_normal = normalize(world_normal);
	return (world_normal);
}

t_vec3	reflect(t_vec3 in, t_vec3 normal)
{
	t_vec3	result;
	t_vec3	scaled_norm;

	scaled_norm = multiplication(normal, 2 * dot_product(in, normal));
	result = subtraction(in, scaled_norm);
	return (result);
}
