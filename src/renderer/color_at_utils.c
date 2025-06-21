#include "minirt.h"

/**
 * @brief Checks if the light is behind the surface.
 * @param l_dot_norm Dot product of light vector and surface normal.
 * @return true if the light is behind the surface, false otherwise.
 */
bool	light_behind_surface(float l_dot_norm)
{
	if (l_dot_norm < 0)
		return (true);
	return (false);
}

/**
 * @brief Sets the diffuse and specular color components to dark (zero).
 * @param pc Pointer to the phong color structure.
 */
void	set_dark(t_phong_color *pc)
{
	pc->dif = (t_color){0.0f, 0.0f, 0.0f};
	pc->spec = (t_color){0.0f, 0.0f, 0.0f};
}

/**
 * @brief Calculates and sets the diffuse and specular color components.
 *
 * Computes the diffuse and specular contributions for the Phong lighting model.
 *
 * @param pc Pointer to the phong color structure.
 * @param m Pointer to the material.
 * @param v Pointer to the phong variables.
 * @param l The light source.
 */
void	set_color(t_phong_color *pc, t_material *m, t_phong_vars *v, t_light l)
{
	pc->dif = multiplication(pc->eff_col, m->diffuse * pc->l_dot_norm);
	pc->reflectv = reflect(negation(pc->lightv), v->normalv);
	pc->refl_dot_eye = dot_product(pc->reflectv, v->eyev);
	if (pc->refl_dot_eye <= 0)
		pc->spec = (t_color){0.0f, 0.0f, 0.0f};
	else
	{
		pc->factor = powf(pc->refl_dot_eye, m->shininess);
		pc->spec = multiplication(l.intensity, m->specular * pc->factor);
	}
}

/**
 * @brief Determines if a point is in shadow with respect to a light source.
 *
 * @param rt Pointer to the main program structure.
 * @param point The point to check for shadow.
 * @param light_pos The position of the light source.
 * @return true if the point is in shadow, false otherwise.
 */
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
