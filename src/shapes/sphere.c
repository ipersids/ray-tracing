
#include "minirt.h"

t_intersections	intersect_sphere(t_sphere sphere, t_ray ray)
{
	t_intersections	result;
	t_vec3			oc;
	float			a;
	float			b;
	float			c;
	float			discriminant;
	float			t1;
	float			t2;

	ray.dir = matrix_multiply_vector(sphere.inv_transform, ray.dir);
	ray.orig = matrix_multiply_point(sphere.inv_transform, ray.orig);

	oc = subtraction(ray.orig, sphere.center);
	a = dot_product(ray.dir, ray.dir);
	b = 2.0 * dot_product(ray.dir, oc);
	c = dot_product(oc, oc) - sphere.r * sphere.r;
	discriminant = (b * b) - (4 * a * c);
	result.count = 0;
	if (discriminant < 0)
		return (result);
	t1 = (-b - sqrtf(discriminant)) / (2.0 * a);
	t2 = (-b + sqrtf(discriminant)) / (2.0 * a);
	result.t[0] = t1;
	result.t[1] = t2;
	result.count = 2;
	return (result);
}

t_vec3	sphere_normal_at(t_sphere *sp, t_point world_point)
{
	t_vec3		obj_point;
	t_vec3		obj_normal;
	t_vec3		world_normal;

	obj_point = matrix_multiply_point(sp->inv_transform, world_point);
	obj_normal = subtraction(obj_point, sp->center);
	world_normal = matrix_multiply_vector(sp->inv_transpose, obj_normal);
	world_normal = normalize(world_normal);
	return (world_normal);
}
