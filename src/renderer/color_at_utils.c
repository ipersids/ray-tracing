#include "minirt.h"

bool	light_behind_surface(float l_dot_norm)
{
	if (l_dot_norm < 0)
		return (true);
	return (false);
}

void	set_dark(t_phong_color *pc)
{
	pc->dif = (t_color){0,0,0};
	pc->spec = (t_color){0,0,0};
}

void	set_color(t_phong_color *pc, t_material *m, t_phong_vars *vars, t_light light)
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

bool	in_shadow(t_info *rt, t_point point, t_point light_pos)
{
	t_in_shadow_vars	var;
	var.dir_to_light = subtraction(light_pos, point);
	var.distance_to_light = magnitude(var.dir_to_light);
	var.direction = normalize(var.dir_to_light);
	var.shadow_ray = (t_ray){point, var.direction, RAY_SHADOW};
	rt_intersect_world(rt, &var.shadow_ray);
	var.hit = find_closest_intersection(rt->ts, rt->n_ts);
	if (var.hit && var.hit->t < var.distance_to_light)
		return (true);
	return (false);
}
