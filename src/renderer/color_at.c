#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static t_phong_vars	precompute_data(t_intersection *t, t_ray *ray, t_info *rt);
static t_color		lighting(t_phong_vars vars, t_material m, t_light *light, bool in_shadow);
static bool			light_behind_surface(float l_dot_norm);
static bool			in_shadow(t_info *rt, t_point point);
static void			set_dark(t_phong_color *pc);
static void			set_color(t_phong_color *pc, t_material *m, t_phong_vars *vars, t_light light);
t_color				reflected_color(t_info *rt, t_phong_vars vars, int remaining);

static void		prepare_refraction_calculations(t_info *rt, t_intersection *target, float *n1, float *n2);
static void		update_container(t_obj_container *container, t_object *object);
static bool		is_inside_container(t_obj_container *container, t_object *object, int *index);
static void 	remove_from_container(t_obj_container *container, int index);
static void 	add_to_container(t_obj_container *container, t_object *obj);
static float	get_refractive_index(t_obj_container *container);
t_color			refracted_color(t_info *rt, t_phong_vars vars, int remaining);
float			schlick(t_phong_vars vars);
t_color				reflected_color(t_info *rt, t_phong_vars vars, int ray_bounces);

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
	t_phong_vars	v;

	v.t = t->t;
	v.obj = &rt->objs[t->i_object];
	v.point = ray_hit(*ray, t->t);
	v.eyev = negation(ray->dir);
	v.normalv = rt_normal_at(rt, v.obj, v.point, t->obj_type);
	v.is_inside = false;
	prepare_refraction_calculations(rt, t, &v.n1, &v.n2);
	if (dot_product(v.normalv, v.eyev) < 0.0f)
	{
		v.is_inside = true;
		v.normalv = negation(v.normalv);
	}
	v.reflectv = reflect(ray->dir, v.normalv);
	v.point = addition(v.point, v.normalv);
	v.over_point = addition(v.point, multiplication(v.normalv, SHADOW_BIAS));
	v.under_point = subtraction(v.point, (multiplication(v.normalv, SHADOW_BIAS)));
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

static void	update_container(t_obj_container *container, t_object *object)
{
	int index;

	if (is_inside_container(container, object, &index))
		remove_from_container(container, index);
	else
		add_to_container(container, object);
}

static bool	is_inside_container(t_obj_container *container, t_object *object, int *index)
{
	int	i;

	i = 0;
	while (i < container->obj_count)
	{
		if (container->objs[i] == object)
		{
			*index = i;
			return (true);
		}
		i++;
	}
	return (false);
}

static void remove_from_container(t_obj_container *container, int index)
{
	int i = index;
	while (i < container->obj_count - 1)
	{
		container->objs[i] = container->objs[i + 1];
		i++;
	}
	container->obj_count--;
}

static void add_to_container(t_obj_container *container, t_object *obj)
{
		container->objs[container->obj_count] = obj;
		container->obj_count++;
}

static float	get_refractive_index(t_obj_container *container)
{
	if (container->obj_count == 0)
		return (1.0f);
	else
		return (container->objs[container->obj_count - 1]->material->refractive);
}

t_color	refracted_color(t_info *rt, t_phong_vars vars, int remaining)
{
	t_color	result;
	t_ray	refracted_ray;
	t_vec3	direction;
	float	n_ratio;
	float	cos_i;
	float	sin2_t;
	float	cos_t;

	if (remaining <= 0 || vars.obj->material->transparency == 0)
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
	result = rt_color_at(rt, &refracted_ray, remaining - 1);
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
