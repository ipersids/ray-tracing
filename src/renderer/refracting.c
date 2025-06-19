#include "minirt.h"

void	prepare_refraction_calculations(t_info *rt, t_intersection *target, float *n1, float *n2)
{
	t_obj_container	container;
	t_object		*object;
	size_t				i;

	container.obj_count = 0;
	*n1 = 1.0f;
	*n2 = 1.0f;
	i = 0;
	while (i < rt->n_ts)
	{
			object = &rt->objs[rt->ts[i].i_object];
			if (&rt->ts[i] == target)
			{
				*n1 = get_refractive_index(&container);
				update_container(&container, object);
				*n2 = get_refractive_index(&container);
				return;
			}
			update_container(&container, object);
			i++;
	}
}

t_color	refracted_color(t_info *rt, t_phong_vars vars, int ray_bounces)
{
	t_color	result;
	t_ray	refracted_ray;
	t_vec3	direction;
	float	n_ratio;
	float	cos_i;
	float	sin2_t;
	float	cos_t;

	if (vars.obj->material->transparency == 0)
		return (BLACK);
	if (ray_bounces <= 0)
		return (BLACK);
	n_ratio = vars.n1 / vars.n2;
	cos_i = dot_product(vars.eyev, vars.normalv);
	sin2_t = n_ratio * n_ratio * (1 - cos_i * cos_i);
	if (sin2_t > 1)
		return (BLACK);
	cos_t = sqrtf(1.0 - sin2_t);
	direction = subtraction(multiplication(vars.normalv, n_ratio * cos_i - cos_t),
			multiplication(vars.eyev, n_ratio));
	refracted_ray = (t_ray){vars.under_point, direction, RAY_REFRACTION};
	result = rt_color_at(rt, &refracted_ray, ray_bounces - 1);
	return (multiplication(result, vars.obj->material->transparency));
}

float	schlick(t_phong_vars vars)
{
	float	cos;
	float	cos_t;
	float	n_ratio;
	float	sin2_t;
	float	reflectance;

	cos = dot_product(vars.eyev, vars.normalv);
	if (vars.n1 > vars.n2)
	{
		n_ratio = vars.n1 / vars.n2;
		sin2_t = n_ratio * n_ratio * (1 - cos * cos);
		if (sin2_t > 1)
			return (1.0);
		cos_t = sqrtf(1.0f - sin2_t);
		cos = cos_t;
	}
	reflectance = ((vars.n1 - vars.n2) / (vars.n1 + vars.n2));
	reflectance = reflectance * reflectance;
	return (reflectance + (1 - reflectance) * powf(1 - cos, 5));
}
