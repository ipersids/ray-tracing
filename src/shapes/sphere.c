
#include "minirt.h"

t_vec3	matrix_multiply_vector(t_matrix m, t_vec3 v);

t_ray	transform_ray(t_ray ray, t_matrix matrix)// REMOVE FROM HERE
{
	t_ray	result;

	result.orig = matrix_multiply_vec3(matrix, ray.orig);
	result.dir = matrix_multiply_vec3(matrix, ray.dir);
	return (result);
}

t_vec3	matrix_multiply_vector(t_matrix m, t_vec3 v)// REMOVE FROM HERE
{
	t_vec3	result;

	result.x = m.data[0][0] * v.x + m.data[0][1] * v.y + m.data[0][2] * v.z;
	result.y = m.data[1][0] * v.x + m.data[1][1] * v.y + m.data[1][2] * v.z;
	result.z = m.data[2][0] * v.x + m.data[2][1] * v.y + m.data[2][2] * v.z;
	return (result);
}

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

	//t_ray transformed_ray = transform_ray(ray, sphere.inv_transform);

	oc = subtraction(ray.orig, sphere.pos);
	//oc = transformed_ray.orig;
	// a = dot_product(transformed_ray.dir, transformed_ray.dir);
	// b = 2.0 * dot_product(transformed_ray.dir, oc);
	a = dot_product(ray.dir, ray.dir);
	b = 2.0 * dot_product(ray.dir, oc);
	c = dot_product(oc, oc) - sphere.r * sphere.r;
	discriminant = (b * b) - (4 * a * c);
	result.count = 0;
	if (discriminant < 0)
		return (result);
	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	result.t[0] = t1;
	result.t[1] = t2;
	//printf("t1 = %.2f t2= %.2f\n", t1, t2);
	result.count = 2;
	return (result);
}

		//THIS DOES NOT WORK YET, SOMETHING WRONG WITH THE INVERSE

// t_intersections	intersect_sphere(t_sphere sphere, t_ray ray)
// {
// 	t_intersections	result;
// 	t_vec3			oc;
// 	float			a;
// 	float			b;
// 	float			c;
// 	float			discriminant;
// 	float			t1;
// 	float			t2;
// 	// t_ray			transformed_ray;
//  	// t_matrix		inv;

// 	// inv = inverse(sphere.transform);
// 	// transformed_ray = transform_ray(ray, inv);
// 	// transformed_ray.orig = matrix_multiply_point(inv, ray.orig);
// 	// transformed_ray.dir = matrix_multiply_vec3(inv, ray.dir);

// 	oc = subtraction(ray.orig, sphere.pos);
// 	//oc = transformed_ray.orig;
// 	a = dot_product(ray.dir, ray.dir);
// 	b = 2.0 * dot_product(ray.dir, oc);
// 	c = dot_product(oc, oc) - sphere.r * sphere.r;
// 	//c = dot_product(oc, oc) - 1.0f;
// 	discriminant = (b * b) - (4 * a * c);
// 	result.count = 0;
// 	if (discriminant < 0)
// 	{
// 		//printf("No hit\n");
// 		return (result);
// 	}
// 	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
// 	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
// 	result.t_values[0].t = t1;
// 	result.t_values[1].t = t2;
// 	result.count = 2;
// 	return (result);
// }

// FINAL VERSION SHOULD TAKE SPHERE AND NOT COORDINATES

void	set_sphere_default(t_sphere sphere)
{
	sphere.transform = matrix_identity();
}

void	set_sphere_transform(t_sphere sphere, t_matrix transform)
{
	sphere.transform = transform;
}

//HAVE TO CHECK THIS ONE, NOT SURE ABOUT IT

// t_intersections	hit_sphere(t_sphere sphere, t_ray ray)
// {
// 	t_intersections	result;
// 	t_vec3			oc;
// 	t_ray			transformed_ray;
// 	t_matrix		inv;
// 	float			a;
// 	float			b;
// 	float			c;
// 	float			discriminant;
// 	float			t1;
// 	float			t2;

// 	inv = inverse(sphere.transform);
// 	transformed_ray.orig = matrix_multiply_vec3(inv, ray.orig);
// 	transformed_ray.dir = matrix_multiply_vec3(inv, ray.dir);

// 	oc = transformed_ray.orig;
// 	a = dot_product(transformed_ray.dir, transformed_ray.dir);
// 	b = 2.0 * dot_product(transformed_ray.dir, oc);
// 	c = dot_product(oc, oc) - 1.0;
// 	discriminant = (b * b) - (4 * a * c);
// 	result.count = 0;
// 	if (discriminant < 0)
// 		return (result);
// 	t1 = (-b - sqrtf(discriminant)) / (2.0 * a);
// 	t2 = (-b + sqrtf(discriminant)) / (2.0 * a);
// 	result.t_values[0].t = t1;
// 	result.t_values[1].t = t2;
// 	result.count = 2;
// 	return (result);
// }
