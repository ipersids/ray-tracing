/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_at.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:38:57 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/30 15:55:46 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static t_phong_vars	prepare_shading(t_intersection *t, t_ray *ray, t_info *rt);
static t_color	lighting(t_phong_vars vars, t_material m, t_plight light);
static bool	light_behind_surface(float l_dot_norm);

/* --------------------------- Public Functions ---------------------------- */

t_color	rt_color_at(t_info *rt, t_ray *ray)
{
	t_intersection	*t;
	t_phong_vars	vars;
	t_color			result;
	t_plight		light;//TODO REMOVE

	t = NULL;
	rt_intersect_world(rt, ray);
	t = find_closest_intersection(rt->ts, rt->n_ts);
	if (NULL == t)
		return ((t_color){0.0f, 0.0f, 0.0f});
	vars = prepare_shading(t, ray, rt);
	// vars.obj->material = default_material();
	// vars.obj->material.color = vars.obj->sp.color;
	light.position = rt->lights[0].pos;
	light.intensity = (t_color){1.0f, 1.0f, 1.0f};
	result = lighting(vars, *vars.obj->material, light);
	return (result);
}

/* ------------------- Private Function Implementation --------------------- */

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

static t_color	lighting(t_phong_vars vars, t_material m, t_plight light)
{
 	t_phong_color pc;

 	pc.eff_col = multiply_colors(m.color, light.intensity);
 	pc.lightv = normalize(subtraction(light.position, vars.point));
 	pc.amb = multiply_colors(pc.eff_col, m.ambient_comp);
 	pc.l_dot_norm = dot_product(pc.lightv, vars.normalv);
 	if (light_behind_surface(pc.l_dot_norm))
 	{
 		pc.dif = (t_color){0,0,0};
 		pc.spec = (t_color){0,0,0};
 	}
 	else
 	{
 		pc.dif = multiplication(pc.eff_col, m.diffuse * pc.l_dot_norm);
 		pc.reflectv = reflect(negation(pc.lightv), vars.normalv);
 		pc.refl_dot_eye = dot_product(pc.reflectv, vars.eyev);
 		if (pc.refl_dot_eye <= 0)
 			pc.spec = (t_color){0,0,0};
 		else
 		{
 			pc.factor = powf(pc.refl_dot_eye, m.shininess);
 			pc.spec = multiplication(light.intensity, m.specular * pc.factor);
 		}
	}
	return(addition(addition(pc.amb, pc.dif), pc.spec));
}

static bool	light_behind_surface(float l_dot_norm)
{
	if (l_dot_norm < 0)
		return (true);
	return (false);
}

// static bool	in_shadow(world, t_point point, t_plight light)
// {
// 	float	distance_to_light;
// 	t_vec3	direction;
// 	t_ray	ray;

// 	direction = subtraction(point, light.position);
// 	distance_to_light = magnitude(direction);
// 	ray = normalize(direction);
// }

































/*
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
}*/
