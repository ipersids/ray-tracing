
#include "minirt.h"

// void	set_sphere_transform(t_sphere sphere, t_matrix transform);

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

// void	set_sphere_default(t_sphere sphere)
// {
// 	sphere.transform = matrix_identity();
// }

// void	set_sphere_transform(t_sphere sphere, t_matrix transform)
// {
// 	sphere.transform = transform;
// }
