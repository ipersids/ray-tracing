/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_at.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reerikai <reerikai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:38:57 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/02 19:00:59 by reerikai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static t_phong_vars	prepare_shading(t_intersection *t, t_ray *ray, t_info *rt);
static t_color		lighting(t_phong_vars vars, t_material m, t_light *light, bool in_shadow);
static bool			light_behind_surface(float l_dot_norm);
static bool			in_shadow(t_info *rt, t_point point);
static void			set_dark(t_phong_color *pc);
static void			set_color(t_phong_color *pc, t_material *m, t_phong_vars *vars, t_light light);
static t_pat		stripe_pattern(t_color a, t_color b, t_pattype type);
static t_color		stripe_pattern_at(t_pat *pattern, t_point point);
//static t_pat		no_pattern();
//static t_color		stripe_at_object(t_pat *pat, t_object obj, t_point point);

/* --------------------------- Public Functions ---------------------------- */

t_color	rt_color_at(t_info *rt, t_ray *ray)
{
	t_intersection	*t;
	t_phong_vars	vars;
	t_color			result;
	bool			shadowed;

	t = NULL;
	rt_intersect_world(rt, ray);
	t = find_closest_intersection(rt->ts, rt->n_ts);
	if (NULL == t)
		return ((t_color){0.0f, 0.0f, 0.0f});
	vars = prepare_shading(t, ray, rt);
	shadowed = in_shadow(rt, vars.point);
	if (vars.obj->id == ELEMENT_SPHERE)
		vars.obj->material->pattern = stripe_pattern((t_color){1,1,1}, (t_color){0,0,0}, PATTERN_STRIPE);
	//vars.obj->material->pattern = no_pattern();
	result = lighting(vars, *vars.obj->material, rt->lights, shadowed);
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

static t_color	lighting(t_phong_vars vars, t_material m, t_light *light, bool in_shadow)
{
 	t_phong_color	pc;
	t_color			surface_color;

	if (!light)
		return (m.ambient_comp);
	if (m.pattern.has_pattern == true)
		surface_color = stripe_pattern_at(&m.pattern, vars.point);
		//surface_color = stripe_at_object(&m.pattern, *vars.obj, vars.point);
	else
		surface_color = m.color;
 	pc.eff_col = multiply_colors(surface_color, light[0].intensity);
 	pc.lightv = normalize(subtraction(light[0].pos, vars.point));
 	pc.amb = multiply_colors(pc.eff_col, m.ambient_comp);
	if (in_shadow)
		return (pc.amb);
 	pc.l_dot_norm = dot_product(pc.lightv, vars.normalv);
 	if (light_behind_surface(pc.l_dot_norm))
		set_dark(&pc);
 	else
		set_color(&pc, &m, &vars, light[0]);
	return(addition(addition(pc.amb, pc.dif), pc.spec));
}

static bool	light_behind_surface(float l_dot_norm)
{
	if (l_dot_norm < 0)
		return (true);
	return (false);
}

static void	set_dark(t_phong_color *pc)
{
	pc->dif = (t_color){0,0,0};
	pc->spec = (t_color){0,0,0};
}

static void	set_color(t_phong_color *pc, t_material *m, t_phong_vars *vars, t_light light)
{
	pc->dif = multiplication(pc->eff_col, m->diffuse * pc->l_dot_norm);
	pc->reflectv = reflect(negation(pc->lightv), vars->normalv);
	pc->refl_dot_eye = dot_product(pc->reflectv, vars->eyev);
	if (pc->refl_dot_eye <= 0)
		pc->spec = (t_color){0,0,0};
	else
	{
		pc->factor = powf(pc->refl_dot_eye, m->shininess);
		pc->spec = multiplication(light.intensity, m->specular * pc->factor);
	}
}

static bool	in_shadow(t_info *rt, t_point point)
{
	float			distance_to_light;
	t_vec3			dir_to_light;
	t_vec3			direction;
	t_ray			shadow_ray;
	t_intersection	*hit;

	dir_to_light = subtraction(rt->lights->pos, point);
	distance_to_light = magnitude(dir_to_light);
	direction = normalize(dir_to_light);
	shadow_ray = (t_ray){point, direction, RAY_SHADOW};
	rt_intersect_world(rt, &shadow_ray);
	hit = find_closest_intersection(rt->ts, rt->n_ts);
	if (hit && hit->t < distance_to_light)
		return (true);
	return (false);
}

static t_pat	stripe_pattern(t_color a, t_color b, t_pattype type)
{
	t_pat	pattern;

	pattern.type = type;
	pattern.color_a = a;
	pattern.color_b = b;
	pattern.has_pattern = true;
	return (pattern);
}

// static t_pat	no_pattern()
// {
// 	t_pat	pattern;

// 	pattern.has_pattern = false;
// 	return (pattern);
// }

// static t_color	stripe_at_object(t_pat *pat, t_object obj, t_point point)
// {
// 	t_matrix	obj_inv;
// 	t_matrix	pat_inv;
// 	t_point		object_point;
// 	t_point		pattern_point;
// 	t_color		res;

// 	if (!matrix_try_inverse(obj.transform, &obj_inv))
// 		obj_inv = matrix_identity();
// 	object_point = matrix_multiply_point(obj_inv, point);
// 	if (!matrix_try_inverse(pat->transform, &pat_inv))
// 		pat_inv = matrix_identity();
// 	pattern_point = matrix_multiply_point(pat_inv, object_point);
// 	res = stripe_pattern_at(pat, pattern_point);
// 	return (res);
// }

static t_color	stripe_pattern_at(t_pat *pattern, t_point point)
{
	if ((int)floorf(point.x) % 2 == 0) // floof?
		return (pattern->color_a);
	else
		return (pattern->color_b);
}































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
