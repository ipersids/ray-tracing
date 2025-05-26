#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Calculates a primary ray from the camera's eye-point to a pixel.
 *
 * This function computes the ray direction for a given pixel on the viewport.
 * The ray originates from the camera's position and points toward the center
 * of the specified pixel.
 *
 * @param camera Pointer to the camera structure.
 * @param px The x-coordinate of the pixel.
 * @param py The y-coordinate of the pixel.
 * @return t_ray The calculated ray with origin, direction, and type.
 */
t_ray	rt_get_ray(t_camera *camera, int32_t px, int32_t py)
{
	t_point	px_center;
	t_vec3	ray_direction;

	px_center = addition(camera->px00_loc, addition(
				multiplication(camera->px_delta_u, px),
				multiplication(camera->px_delta_v, py)));
	ray_direction = normalize(subtraction(px_center, camera->pos));
	return ((t_ray){camera->pos, ray_direction, RAY_CAMERA});
}

t_vec3	ray_hit(t_ray ray, float t)
{
	t_vec3 scaled_direction;

	scaled_direction = multiplication(ray.dir, t);
	return addition(ray.orig, scaled_direction);
}

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

t_color	ray_color(t_ray ray, t_sphere sphere)
{
	float			t;
	float			a;
	t_intersections	hits;
	t_vec3			n;
	t_vec3			unit_direction;
	t_vec3			hit_location;
	t_color			color;
	t_color			white;
	t_color			blue;
	t_color			black;

	white = (t_color){0.0, 1.0, 0.5};
	blue = (t_color){0.5, 0.7, 1.0};
	black = (t_color){0.0, 0.0, 0.0};
	hits = intersect_sphere(sphere, ray);
	t = find_closest_intersection(hits);
	if (t > 0.0)
	{
		hit_location = ray_hit(ray, t);
		n = normalize(subtraction(hit_location, sphere.pos));
		//n = normal_at(sphere, hit_location);
		color = multiplication(sphere.color, 1.5f);
		return (color);
	}
	unit_direction = normalize(ray.dir);
	a = 0.5 * (unit_direction.y + 1.0);
	//color = addition(multiplication(white, 1.0 - a), multiplication(blue, a));
	color = black;
	return (color);
}

t_vec3	normal_at(t_sphere sphere, t_point world_point)
{
	t_vec3		object_point;
	t_vec3		object_normal;
	t_vec3		world_normal;
	t_matrix	inv;
	t_matrix	inv_transpose;

	inv = inverse(sphere.transform);
	object_point = matrix_multiply_vec3(inv, world_point);
	object_normal = subtraction(object_point, (t_point){0, 0, 0});
	inv_transpose = matrix_transpose(inv);
	world_normal = matrix_multiply_vec3(inv_transpose, object_normal);
	world_normal = normalize(world_normal);
	return(world_normal);
}

// t_vec3	reflect(t_vec3 in, t_vec3 normal)
// {
// 	t_vec3	result;
// 	t_vec3	scaled_norm;

// 	scaled_norm = multiplication(normal, 2 * dot_product(in, normal));
// 	result = subtraction(in, scaled_norm);
// 	return (result);
// }

t_sphere	init_sphere(void)
{
	t_sphere	sphere;


	sphere.pos = (t_point){-50.0f, 0.0f, 70.0f};
	sphere.r = 10.0;
	sphere.color = (t_color){1, 0, 0};
	sphere.transform = matrix_identity();
	return (sphere);
}
