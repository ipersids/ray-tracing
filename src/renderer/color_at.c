#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static t_phong_vars	precompute_data(t_intersection *t, t_ray *ray, t_info *rt);
static t_color		lighting(t_phong_vars vars, t_material m, t_light *light, bool in_shadow);
static bool			light_behind_surface(float l_dot_norm);
static bool			in_shadow(t_info *rt, t_point point);
static void			set_dark(t_phong_color *pc);
static void			set_color(t_phong_color *pc, t_material *m, t_phong_vars *vars, t_light light);
t_color				reflected_color(t_info *rt, t_phong_vars vars, int ray_bounces);

/* --------------------------- Public Functions ---------------------------- */

t_color	rt_color_at(t_info *rt, t_ray *ray, int ray_bounces)
{
	t_intersection	*t;
	t_phong_vars	vars;
	t_color			surface;
	t_color			reflected;
	bool			shadowed;

	t = NULL;
	rt_intersect_world(rt, ray);
	t = find_closest_intersection(rt->ts, rt->n_ts);
	if (NULL == t)
		return ((t_color){0.0f, 0.0f, 0.0f});
	vars = precompute_data(t, ray, rt);
	if (!rt->lights)
		return (multiply_colors(vars.obj->color, rt->amb_intensity));
	shadowed = in_shadow(rt, vars.point);
	surface = lighting(vars, *vars.obj->material, rt->lights, shadowed);
	reflected = reflected_color(rt, vars, ray_bounces);
	return (addition(surface, reflected));
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
	v.is_inside = false;
	if (dot_product(v.normalv, v.eyev) < 0.0f)
	{
		v.is_inside = true;
		v.normalv = negation(v.normalv);
	}
	v.reflectv = reflect(ray->dir, v.normalv);
	v.point = addition(v.point, v.normalv);
	v.over_point = addition(v.point, multiplication(v.normalv, SHADOW_BIAS));
	if (v.obj->has_texture == true)
		v.texture = rt->win.texture[v.obj->tex_type];
	return (v);
}

static t_color	lighting(t_phong_vars vars, t_material m, t_light *light, bool in_shadow)
{
 	t_phong_color	pc;
	t_color			surface_color;

	if (!light)
		return (vars.obj->amb_component);
	if (vars.obj->has_pattern == true)
		surface_color = pattern_at_object(*vars.obj->pattern, *vars.obj, vars.point);
	else if (vars.obj->has_texture == true)
	{
		t_uv_vars uv = rt_get_uv_coordinates(vars.obj, &vars.point);
		surface_color = rt_texture_color_at(vars.texture, uv.u, uv.v);
	}
	else
		surface_color = vars.obj->color;
 	pc.eff_col = multiply_colors(surface_color, light[0].intensity);
 	pc.lightv = normalize(subtraction(light[0].pos, vars.point));
 	pc.amb = multiply_colors(pc.eff_col, vars.obj->amb_component);
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

t_color	reflected_color(t_info *rt, t_phong_vars vars, int ray_bounces)
{
	t_ray	reflected_ray;
	t_color	reflected_color;

	if (vars.obj->material->reflective == 0)
		return (BLACK);
	if (ray_bounces <= 0)
		return (BLACK);
	reflected_ray = (t_ray){vars.point, vars.reflectv, RAY_REFLECTION};
	reflected_color = rt_color_at(rt, &reflected_ray, ray_bounces - 1);
	return (multiplication(reflected_color, vars.obj->material->reflective));
}
