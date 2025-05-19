
#include "minirt.h"

/*		FOR THE SECOND TEST		*/

/*
	The hit sphere should return a struct where you can store
	both of the t values (entry point and exit point)
*/

// float	hit_sphere(t_point center, float radius, t_ray ray)
// {
// 	t_vec3	oc;
// 	float	a;
// 	float	b;
// 	float	c;
// 	float	discriminant;

// 	oc = subtraction(ray.orig, center);
// 	a = dot_product(ray.dir, ray.dir);
// 	b = 2.0 * dot_product(ray.dir, oc);
// 	c = dot_product(oc, oc) - radius * radius;
// 	discriminant = (b * b) - (4 * a * c);
// 	if (discriminant < 0)
// 		return (-1.0);
// 	else
// 		return((-b - sqrt(discriminant)) / (2.0 * a));
// }

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
