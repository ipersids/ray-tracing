#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static t_phong_vars	precompute_data(t_intersection *t, t_ray *ray, t_info *rt);
static t_color		lighting(t_phong_vars vars, t_material m, t_light *light, bool in_shadow);


/* --------------------------- Public Functions ---------------------------- */

t_color	rt_color_at(t_info *rt, t_ray *ray, int ray_bounces)
{
	t_intersection	*t;
	t_phong_vars	vars;
	t_color			surface;
	t_color			reflected;
	t_color			refracted;
	bool			shadowed;
	float			reflectance;

	//printf("The ray bounces: %d\n", ray_bounces);
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
	refracted = refracted_color(rt, vars, ray_bounces);
	if (vars.obj->material->reflective > 0 && vars.obj->material->transparency > 0)
	{
		reflectance = schlick(vars);
		return (addition(surface, (addition(multiplication(reflected, reflectance),
				multiplication(refracted, 1 - reflectance)))));
	}
	return (addition(addition(surface, reflected), refracted));
}

/* ------------------- Private Function Implementation --------------------- */

static t_phong_vars	precompute_data(t_intersection *t, t_ray *ray, t_info *rt)
{
	t_phong_vars	vars;

	vars.t = t->t;
	vars.obj = &rt->objs[t->i_object];
	vars.point = ray_hit(*ray, t->t);
	vars.eyev = negation(ray->dir);
	vars.normalv = rt_normal_at(vars.obj, vars.point, t->obj_type);
	vars.reflectv = reflect(ray->dir, vars.normalv);
	prepare_refraction_calculations(rt, t, &vars.n1, &vars.n2);
	if (dot_product(vars.normalv, vars.eyev) < 0.0f)
	{
		vars.is_inside = true;
		vars.normalv = negation(vars.normalv);
		vars.under_point = subtraction(vars.point, (multiplication(vars.normalv, SHADOW_BIAS)));
		return (vars);
	}
	vars.under_point = subtraction(vars.point, (multiplication(vars.normalv, SHADOW_BIAS)));
	vars.point = addition(vars.point, vars.normalv);
	vars.is_inside = false;
	return (vars);
}

static t_color	lighting(t_phong_vars vars, t_material m, t_light *light, bool in_shadow)
{
 	t_phong_color	pc;
	t_color			surface_color;

	if (!light)
		return (vars.obj->amb_component);
	if (vars.obj->has_pattern == true)
		surface_color = pattern_at_object(*vars.obj->pattern, *vars.obj, vars.point);
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




