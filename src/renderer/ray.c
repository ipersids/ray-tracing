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
	size_t		i;
	float		result;

	i = 0;
	result = -1;
	while (i < hits.count)
	{
		if (hits.t[i] > 0.0)
		{
			if (result < 0 || hits.t[i] < result)
				result = hits.t[i];
		}
		i++;
	}
	return (result);
}

t_vec3	normal_at(t_sphere sphere, t_point world_point)
{
	t_vec3		object_point;
	t_vec3		object_normal;
	t_vec3		world_normal;

	object_point = matrix_multiply_vec3(sphere.inv_transform, world_point);
	object_normal = subtraction(object_point, sphere.pos);
	world_normal = matrix_multiply_vec3(sphere.inv_transpose, object_normal);
	world_normal = normalize(world_normal);
	return(world_normal);
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
		//n = normalize(subtraction(hit_location, sphere.pos));
		n = normal_at(sphere, hit_location);
		color = multiplication(sphere.color, 1.5f);
		return (color);
	}
	unit_direction = normalize(ray.dir);
	a = 0.5 * (unit_direction.y + 1.0);
	//color = addition(multiplication(white, 1.0 - a), multiplication(blue, a));
	color = black;
	return (color);
}

t_sphere	init_sphere(t_sphere orig_sphere)
{
	t_sphere	sphere;

	sphere.pos = orig_sphere.pos;
	sphere.center = orig_sphere.center;
	sphere.r = orig_sphere.r;
	sphere.diam = orig_sphere.diam;
	sphere.scale = orig_sphere.scale;
	sphere.color = orig_sphere.color;
	sphere.transform = orig_sphere.transform;
	sphere.inv_transform = orig_sphere.inv_transform;
	sphere.inv_transpose = orig_sphere.inv_transpose;
	return(sphere);
}

// t_plight	point_light(t_color intensity, t_point position)
// {
// 	t_plight	result;

// 	result.intensity = intensity;
// 	result.position = position;
// 	return (result);
// }

// t_material	default_material(void)
// {
// 	t_material	result;

// 	result.color = (t_color){1, 1, 1};
// 	result.ambient = 0.1;
// 	result.diffuse = 0.9;
// 	result.specular = 0.9;
// 	result.shininess = 200;
// 	return (result);
// }

// void	set_material(t_sphere sphere, t_material material)
// {
// 	sphere.material = material;
// }

// t_color	lighting(t_material m, t_point pos, t_plight light, t_vec3 eyev, t_vec3 normalv)
// {
// 	t_color	effective_color;
// 	t_color	ambient;
// 	t_color	diffuse;
// 	t_color	specular;
// 	t_color	result;
// 	t_vec3	lightv;
// 	t_vec3	reflectv;
// 	float	light_dot_normal;
// 	float	reflect_dot_eye;
// 	float	factor;

// 	effective_color = multiply_colors(m.color, light.intensity);
// 	lightv = normalize(subtraction(light.position, pos));
// 	ambient	= multiplication(effective_color, m.ambient);
// 	light_dot_normal = dot_product(lightv, normalv);
// 	if (light_dot_normal < 0)
// 	{
// 		diffuse = (t_color){1, 1, 1};
// 		specular = (t_color){1, 1, 1};
// 	}
// 	else
// 	{
// 		diffuse = multiplication(effective_color, m.diffuse * light_dot_normal);
// 		reflectv = reflect(negation(lightv), normalv);
// 		reflect_dot_eye = dot_product(reflectv, eyev);
// 		if (reflect_dot_eye <= 0)
// 			specular = (t_color){1, 1, 1};
// 		else
// 		{
// 			factor = powf(reflect_dot_eye, m.shininess);
// 			specular = multiplication(light.intensity, m.specular * factor);
// 		}
// 	}
// 	result = addition(addition(ambient, diffuse), specular);
// 	return (result);
// }
