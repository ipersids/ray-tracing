/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_at.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reerikai <reerikai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:38:57 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/27 15:44:32 by reerikai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static t_phong_vars	prepare_shading(t_intersection *t, t_ray *ray, t_info *rt);
//static t_color	lighting(t_phong_vars vars, t_material m, t_plight light);
static t_material	default_material(void);
static void	set_material(t_sphere sphere, t_material material);
static t_plight	point_light(t_point position, t_color intensity);
//static void	print_vector(char *msg, t_vec3 vec);

static t_color	lighting(t_material m, t_point pos, t_plight light, t_vec3 eyev, t_vec3 normalv);

/* --------------------------- Public Functions ---------------------------- */

t_color	rt_color_at(t_info *rt, t_ray *ray)
{
	t_intersection	*t;
	t_phong_vars	vars;
	t_color			result;
	t_material		material;//TODO REMOVE
	t_plight		light;//TODO REMOVE

	t = NULL;
	rt_intersect_world(rt, ray);
	t = find_closest_intersection(rt->ts, rt->n_ts);
	if (NULL == t)
		return ((t_color){0.0f, 0.0f, 0.0f});
	//printf("t = %.2f\n", t->t);
	vars = prepare_shading(t, ray, rt);
	material = default_material();
	material.color = (t_color){1, 0.2, 1};
	set_material(vars.obj->sp, material);
	light = point_light((t_point){-10, 10, -10}, (t_color){1, 1, 1});
	//(void)vars;
	//result = lighting(vars, vars.obj->sp.material, light);
	result = lighting(material, vars.point, light, (t_vec3){0, 0, -1}, (t_vec3){0, 0, -1});
	//print_vector("The result:", result);
	return (result);
}

/* ------------------- Private Function Implementation --------------------- */

void	print_vector(char *msg, t_vec3 vec)
{
	printf("%s x = %.2f y = %.2f z = %.2f\n", msg, vec.x, vec.y, vec.z);
}

static t_phong_vars	prepare_shading(t_intersection *t, t_ray *ray, t_info *rt)
{
	t_phong_vars	vars;

	vars.t = t->t;
	vars.obj = &rt->objs[t->i_object];
	vars.point = ray_hit(*ray, t->t);
	vars.eyev = negation(ray->dir);
	vars.normalv = normal_at(vars.obj, vars.point);
	if (dot_product(vars.normalv, vars.eyev) < 0.0f)
	{
		vars.is_inside = true;
		vars.normalv = negation(vars.normalv);
		return (vars);
	}
	vars.is_inside = false;
	return (vars);
}

static t_plight	point_light(t_point position, t_color intensity)
{
	t_plight	result;

	result.position = position;
	result.intensity = intensity;
	return (result);
}

static t_material	default_material(void)
{
	t_material	result;

	result.color = (t_color){1, 1, 1};
	result.ambient = 0.1;
	result.diffuse = 0.9;
	result.specular = 0.9;
	result.shininess = 200.0;
	return (result);
}

static void	set_material(t_sphere sphere, t_material material)
{
	sphere.material = material;
}

// static t_color	lighting(t_phong_vars vars, t_material m, t_plight light)
// {
// 	t_phong_color pc;

// 	pc.eff_col = multiply_colors(m.color, light.intensity);
// 	pc.lightv = normalize(subtraction(light.position, vars.point));
// 	pc.amb = multiplication(pc.eff_col, m.ambient);
// 	pc.l_dot_norm = dot_product(pc.lightv, vars.normalv);
// 	if (pc.l_dot_norm < 0)
// 	{
// 		pc.dif = (t_color){0,0,0};
// 		pc.spec = (t_color){0,0,0};
// 	}
// 	else
// 	{
// 		pc.dif = multiplication(pc.eff_col, m.diffuse * pc.l_dot_norm);
// 		pc.reflectv = reflect(negation(pc.lightv), vars.normalv);
// 		pc.refl_dot_eye = dot_product(pc.reflectv, vars.eyev);
// 		if (pc.refl_dot_eye <= 0)
// 			pc.spec = (t_color){0,0,0};
// 		else
// 		{
// 			pc.factor = powf(pc.refl_dot_eye, m.shininess);
// 			pc.spec = multiplication(light.intensity, m.specular * pc.factor);
// 		}
// 	}
// 	return(addition(addition(pc.amb, pc.dif), pc.spec));
// }

t_color	lighting(t_material m, t_point pos, t_plight light, t_vec3 eyev, t_vec3 normalv)
{
	t_color	effective_color;
	t_color	ambient;
	t_color	diffuse;
	t_color	specular;
	t_color	result;
	t_vec3	lightv;
	t_vec3	reflectv;
	float	light_dot_normal;
	float	reflect_dot_eye;
	float	factor;

	effective_color = multiply_colors(m.color, light.intensity);
	lightv = normalize(subtraction(light.position, pos));
	ambient	= multiplication(effective_color, m.ambient);
	light_dot_normal = dot_product(lightv, normalv);

	if (light_dot_normal < 0)
	{
		diffuse = (t_color){0, 0, 0};
		specular = (t_color){0, 0, 0};
	}
	else
	{
		diffuse = multiplication(effective_color, m.diffuse * light_dot_normal);
		reflectv = reflect(negation(lightv), normalv);
		reflect_dot_eye = dot_product(reflectv, eyev);
		if (reflect_dot_eye <= 0)
			specular = (t_color){0, 0, 0};
		else
		{
			factor = powf(reflect_dot_eye, m.shininess);
			specular = multiplication(light.intensity, m.specular * factor);
		}
	}
	result = addition(addition(ambient, diffuse), specular);
	return (result);
}
