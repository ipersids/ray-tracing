#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static t_phong_vars	precompute_data(t_intersection *t, t_ray *ray, t_info *rt);
static t_color		lighting(t_phong_vars vars, t_light *light, bool in_shadow);
static void			set_surface_color(t_phong_vars *vars);

/* --------------------------- Public Functions ---------------------------- */

t_color	rt_color_at(t_info *rt, t_ray *ray, int ray_bounces)
{
	t_intersection	*t;
	t_phong_vars	v;
	t_color_at_vars	at;

	rt_intersect_world(rt, ray);
	t = find_closest_intersection(rt->ts, rt->n_ts);
	if (NULL == t)
		return ((t_color){0.0f, 0.0f, 0.0f});
	v = precompute_data(t, ray, rt);
	if (!rt->lights)
		return (multiply_colors(v.obj->color, rt->amb_intensity));
	at.shadowed = in_shadow(rt, v.point);
	at.surface = lighting(v, rt->lights, at.shadowed);
	at.reflected = reflected_color(rt, v, ray_bounces);
	at.refracted = refracted_color(rt, v, ray_bounces);
	if (v.obj->material->reflective > 0 && v.obj->material->transparency > 0)
	{
		at.reflectance = schlick(v);
		at.tmp_color_one = multiplication(at.reflected, at.reflectance);
		at.tmp_color_two = multiplication(at.refracted, 1 - at.reflectance);
		at.tmp_color_surface = (addition(at.tmp_color_one, at.tmp_color_two));
		return (addition(at.surface, at.tmp_color_surface));
	}
	return (addition(addition(at.surface, at.reflected), at.refracted));
}

/* ------------------- Private Function Implementation --------------------- */

static t_phong_vars	precompute_data(t_intersection *t, t_ray *ray, t_info *rt)
{
	t_phong_vars	vars;

	vars.t = t->t;
	vars.obj = &rt->objs[t->i_object];
	vars.point = ray_hit(*ray, t->t);
	vars.eyev = negation(ray->dir);
	vars.normalv = rt_normal_at(rt, vars.obj, vars.point, t->obj_type);
	prepare_refraction_calculations(rt, t, &vars.n1, &vars.n2);
	if (dot_product(vars.normalv, vars.eyev) < 0.0f)
		vars.normalv = negation(vars.normalv);
	vars.reflectv = reflect(ray->dir, vars.normalv);
	vars.under_point = subtraction(
			vars.point,
			(multiplication(vars.normalv, SHADOW_BIAS))
			);
	vars.point = addition(vars.point, vars.normalv);
	if (vars.obj->has_texture == true)
		vars.texture = rt->win.texture[vars.obj->tex_type];
	set_surface_color(&vars);
	return (vars);
}

static t_color	lighting(t_phong_vars vars, t_light *light, bool in_shadow)
{
	t_phong_color	pc;

	if (!light)
		return (vars.obj->amb_component);
	pc.eff_col = multiply_colors(vars.surface_color, light[0].intensity);
	pc.lightv = normalize(subtraction(light[0].pos, vars.point));
	pc.amb = multiply_colors(pc.eff_col, vars.obj->amb_component);
	if (in_shadow)
		return (pc.amb);
	pc.l_dot_norm = dot_product(pc.lightv, vars.normalv);
	if (light_behind_surface(pc.l_dot_norm))
		set_dark(&pc);
	else
		set_color(&pc, vars.obj->material, &vars, light[0]);
	return (addition(addition(pc.amb, pc.dif), pc.spec));
}

static void	set_surface_color(t_phong_vars *vars)
{
	t_uv_vars	uv;

	if (vars->obj->has_pattern == true)
	{
		vars->surface_color = pattern_at_object(
				*vars->obj->pattern, *vars->obj, vars->point
				);
	}
	else if (vars->obj->has_texture == true)
	{
		uv = rt_get_uv_coordinates(vars->obj, &vars->point);
		vars->surface_color = rt_texture_color_at(vars->texture, uv.u, uv.v);
	}
	else
		vars->surface_color = vars->obj->color;
}
