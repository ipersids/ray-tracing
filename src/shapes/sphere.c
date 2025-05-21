
#include "minirt.h"

t_intersections	hit_sphere(t_point center, float radius, t_ray ray)
{
	t_intersections	result;
	t_vec3			oc;
	float			a;
	float			b;
	float			c;
	float			discriminant;
	float			t1;
	float			t2;

	oc = subtraction(ray.orig, center);
	a = dot_product(ray.dir, ray.dir);
	b = 2.0 * dot_product(ray.dir, oc);
	c = dot_product(oc, oc) - radius * radius;
	discriminant = (b * b) - (4 * a * c);
	result.count = 0;
	if (discriminant < 0)
		return (result);
	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	result.t_values[0].t = t1;
	result.t_values[1].t = t2;
	result.count = 2;
	return (result);
}

// FINAL VERSION SHOULD TAKE SPHERE AND NOT COORDINATES

void	set_sphere_default(t_sphere sphere)
{
	sphere.transform = matrix_identity();
}

// HAVE TO CHECK THIS ONE, NOT SURE ABOUT IT
/*
t_intersections	hit_sphere(t_sphere sphere, t_ray ray)
{
	t_intersections	result;
	t_vec3			oc;
	t_ray			transformed_ray;
	t_matrix		inv;
	float			a;
	float			b;
	float			c;
	float			discriminant;
	float			t1;
	float			t2;

	inv = inverse_matrix(sphere->transform);
	transformed_ray.orig = matrix_multiply_vec3(inv, ray.orig);
	transformed_ray.dir = matrix_multiply_vec3(inv, ray.dir);

	oc = transformed_ray.orig;
	a = dot_product(transformed_ray.dir, transformed_ray.dir);
	b = 2.0 * dot_product(transformed_ray.dir, oc);
	c = dot_product(oc, oc) - 1.0;
	discriminant = (b * b) - (4 * a * c);
	result.count = 0;
	if (discriminant < 0)
		return (result);
	t1 = (-b - sqrtf(discriminant)) / (2.0 * a);
	t2 = (-b + sqrtf(discriminant)) / (2.0 * a);
	result.t_values[0].t = t1;
	result.t_values[1].t = t2;
	result.count = 2;
	return (result);
}*/