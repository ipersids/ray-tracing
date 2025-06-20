#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static t_phong_vars	precompute_data(t_intersection *t, t_ray *ray, t_info *rt);
static t_color		lighting(t_phong_vars vars, t_light *light, bool in_shadow);
static void			set_surface_color(t_phong_vars *vars);
static t_color		compute_fresnel_effect(t_color_at_vars *at, t_phong_vars v);

/* --------------------------- Public Functions ---------------------------- */

t_color	rt_color_at(t_info *rt, t_ray *ray, int ray_bounces)
{
	t_phong_vars	v;
	t_color_at_vars	at;
	size_t			i;

	rt_intersect_world(rt, ray);
	at.t = find_closest_intersection(rt->ts, rt->n_ts);
	if (NULL == at.t)
		return ((t_color){0.0f, 0.0f, 0.0f});
	v = precompute_data(at.t, ray, rt);
	if (!rt->lights)
		return (multiply_colors(v.obj->color, rt->amb_intensity));
	i = 0;
	at.surface = (t_color){0.0f, 0.0f, 0.f};
	while (i < rt->n_lights)
	{
		at.shadowed = in_shadow(rt, v.point, rt->lights[i].pos);
		at.tmp_color_surface = lighting(v, &rt->lights[i], at.shadowed);
		at.surface = addition(at.tmp_color_surface, at.surface);
		++i;
	}
	at.reflected = reflected_color(rt, v, ray_bounces);
	at.refracted = refracted_color(rt, v, ray_bounces);
	if (v.obj->material->reflective > 0 && v.obj->material->transparency > 0)
		return (compute_fresnel_effect(&at, v));
	return (addition(addition(at.surface, at.reflected), at.refracted));
}

/* ------------------- Private Function Implementation --------------------- */

static t_phong_vars	precompute_data(t_intersection *t, t_ray *ray, t_info *rt)
{
	t_phong_vars	v;

	v.t = t->t;
	v.obj = &rt->objs[t->i_object];
	v.point = ray_hit(*ray, t->t);
	v.eyev = negation(ray->dir);
	v.normalv = rt_normal_at(rt, v.obj, v.point, t->obj_type);
	prepare_refraction_calculations(rt, t, &v.n1, &v.n2);
	if (dot_product(v.normalv, v.eyev) < 0.0f)
		v.normalv = negation(v.normalv);
	v.reflectv = reflect(ray->dir, v.normalv);
	v.under_point = subtraction(
			v.point,
			(multiplication(v.normalv, SHADOW_BIAS))
			);
	v.point = addition(v.point, v.normalv);
	if (v.obj->has_texture == true)
		v.texture = rt->win.texture[v.obj->tex_type];
	set_surface_color(&v);
	return (v);
}

static t_color	lighting(t_phong_vars vars, t_light *light, bool in_shadow)
{
	t_phong_color	pc;

	if (!light)
		return (vars.obj->amb_component);
	pc.eff_col = multiply_colors(vars.surface_color, light->intensity);
	pc.amb = multiply_colors(pc.eff_col, vars.obj->amb_component);
	if (in_shadow)
		return (pc.amb);
	pc.lightv = normalize(subtraction(light->pos, vars.point));
	pc.l_dot_norm = dot_product(pc.lightv, vars.normalv);
	if (light_behind_surface(pc.l_dot_norm))
		set_dark(&pc);
	else
		set_color(&pc, vars.obj->material, &vars, *light);
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

static t_color	compute_fresnel_effect(t_color_at_vars *at, t_phong_vars v)
{
	at->reflectance = schlick(v);
	at->tmp_color_one = multiplication(at->reflected, at->reflectance);
	at->tmp_color_two = multiplication(at->refracted, 1 - at->reflectance);
	at->tmp_color_surface = (addition(at->tmp_color_one, at->tmp_color_two));
	return (addition(at->surface, at->tmp_color_surface));
}
