
#include "minirt.h"

/*		FOR THE FIRST TEST		*/

// bool	hit_sphere(t_point center, float radius, t_ray ray)
// {
// 	t_vec3	oc;
// 	float	a;
// 	float	b;
// 	float	c;
// 	float	discriminant; // Discriminant tells us whether there are 2, 1 or 0 solutions

// 	oc = subtraction(center, ray.orig);
// 	a = dot_product(ray.dir, ray.dir);
// 	b = 2.0 * dot_product(ray.dir, oc);
// 	c = dot_product(oc, oc) - radius * radius;
// 	discriminant = (b * b) - (4 * a * c);
// 	if (discriminant < 0)
// 		return (false);
// 	else
// 		return (true);
// 	//return (discriminant >= 0);
// }

/*		FOR THE SECOND TEST		*/

float	hit_sphere(t_point center, float radius, t_ray ray)
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;

	oc = subtraction(ray.orig, center);
	a = dot_product(ray.dir, ray.dir);
	b = 2.0 * dot_product(ray.dir, oc);
	c = dot_product(oc, oc) - radius * radius;
	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (-1.0);
	else
		return((-b - sqrt(discriminant)) / (2.0 * a));
}
