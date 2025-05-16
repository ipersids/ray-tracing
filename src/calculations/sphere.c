
#include "minirt.h"

bool	hit_sphere(t_point center, float radius, t_ray ray)
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant; // Discriminant tells us whether there are 2, 1 or 0 solutions

	oc = subtraction(center, ray.origin);
	a = dot_product(ray.direction, ray.direction);
	b = 2.0 * dot_product(ray.direction, oc);
	c = dot_product(oc, oc) - radius * radius;
	discriminant = (b * b) - (4 * a * c);
	return (discriminant >= 0);
}

t_color	ray_color(t_ray ray)
{
	t_color	color;
	t_color	white;
	t_color	blue;
	t_vec3	unit_direction;
	float	a;

	if (hit_sphere(t_vec3(0, 0, -1), 0.5, ray))
		return ((t_color){1, 0, 0});
	unit_direction = normalize(ray.direction);
	a = 0.5 * (unit_direction.y + 1.0);
	white = (t_color){1.0, 1.0, 1.0};
	blue = (t_color){0.5, 0.7, 1.0};
	color = addition(multiplication(white, 1.0 - a), multiplication(blue, a));
	return (color);
}
