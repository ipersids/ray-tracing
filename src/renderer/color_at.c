#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static t_phong_vars	prepare_shading(t_intersection *t, t_ray *ray, t_info *rt);
static t_color		lighting(t_phong_vars vars, t_material m, t_light *light, bool in_shadow);
static bool			light_behind_surface(float l_dot_norm);
static bool			in_shadow(t_info *rt, t_point point);
static void			set_dark(t_phong_color *pc);
static void			set_color(t_phong_color *pc, t_material *m, t_phong_vars *vars, t_light light);
static t_color		pattern_at_object(t_pat pattern, t_object obj, t_point w_point);
static t_color		stripe_pattern_at(t_pat pattern, t_point point);
static t_color		gradient_pattern_at(t_pat pattern, t_point point);
static t_color		ring_pattern_at(t_pat pattern, t_point point);
static t_color		checker_pattern_at(t_pat pattern, t_point point);
static t_color		radiant_gradient_pattern_at(t_pat pattern, t_point point);
static void			find_object(t_object object, t_matrix *obj_inv);
t_color				reflected_color(t_info *rt, t_phong_vars vars, int remaining);

static void		prepare_refraction_calculations(t_info *rt, t_intersection *target, float *n1, float *n2);
static void		update_container(t_obj_container *container, t_object *object);
static bool		is_inside_container(t_obj_container *container, t_object *object, int *index);
static void 	remove_from_container(t_obj_container *container, int index);
static void 	add_to_container(t_obj_container *container, t_object *obj);
static float	get_refractive_index(t_obj_container *container);
t_color			refracted_color(t_info *rt, t_phong_vars vars, int remaining);

/* --------------------------- Public Functions ---------------------------- */

t_color	rt_color_at(t_info *rt, t_ray *ray, int remaining)
{
	t_intersection	*t;
	t_phong_vars	vars;
	t_color			surface;
	t_color			reflected;
	t_color			refracted;
	bool			shadowed;

	t = NULL;
	rt_intersect_world(rt, ray);
	t = find_closest_intersection(rt->ts, rt->n_ts);
	if (NULL == t)
		return ((t_color){0.0f, 0.0f, 0.0f});
	vars = prepare_shading(t, ray, rt);
	if (!rt->lights)
		return (vars.obj->material->ambient_comp);
	shadowed = in_shadow(rt, vars.point);
	surface = lighting(vars, *vars.obj->material, rt->lights, shadowed);
	reflected = reflected_color(rt, vars, remaining);
	refracted = refracted_color(rt, vars, remaining);
	return (addition(addition(surface, reflected), refracted));
}

/* ------------------- Private Function Implementation --------------------- */

static t_phong_vars	prepare_shading(t_intersection *t, t_ray *ray, t_info *rt)
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
		vars.under_point = subtraction(vars.point, (multiplication(vars.normalv, EPSILON)));
		return (vars);
	}
	vars.under_point = subtraction(vars.point, (multiplication(vars.normalv, EPSILON)));
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
		surface_color = pattern_at_object(m.pattern, *vars.obj, vars.point);
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

static t_color	pattern_at_object(t_pat pattern, t_object obj, t_point w_point)
{
	t_point		object_point;
	t_point		pattern_point;
	t_matrix	obj_inv;

	find_object(obj, &obj_inv);
	object_point = matrix_multiply_vector(obj_inv, w_point);
	pattern_point = matrix_multiply_vector(pattern.inv_transform, object_point);
	if (pattern.type == PATTERN_STRIPE)
		return (stripe_pattern_at(pattern, pattern_point));
	else if (pattern.type == PATTERN_GRADIENT)
		return (gradient_pattern_at(pattern, pattern_point));
	else if (pattern.type == PATTERN_RING)
		return (ring_pattern_at(pattern, pattern_point));
	else if (pattern.type == PATTERN_CHECKER)
		return (checker_pattern_at(pattern, pattern_point));
	else if (pattern.type == PATTERN_RADIANT_GRADIENT)
		return (radiant_gradient_pattern_at(pattern, pattern_point));
	return (BLACK);
}

static t_color	stripe_pattern_at(t_pat pattern, t_point point)
{
	if ((int)floorf(point.x) % 2 == 0)
		return (pattern.color_a);
	else
		return (pattern.color_b);
}

static t_color	gradient_pattern_at(t_pat pattern, t_point point)
{
	t_color	distance;
	float	fraction;

	distance = subtraction(pattern.color_b, pattern.color_a);
	//fraction = fabsf(point.x) - floorf(fabsf(point.x));
	fraction = point.x - floor(point.x);
	//printf("Gradient at x=%.2f -> %.2f\n", point.z, fraction);
	return (addition(pattern.color_a, (multiply_color_scalar(distance, fraction))));
}

static t_color	ring_pattern_at(t_pat pattern, t_point point)
{
	float	distance;

	distance = sqrtf(point.x * point.x + point.z * point.z);
	if ((int)floorf(distance) % 2 == 0)
		return (pattern.color_a);
	else
		return (pattern.color_b);
}

static t_color	checker_pattern_at(t_pat pattern, t_point point)
{
	int sum = (int)(floorf(point.x + EPSILON) +
	                floorf(point.y + EPSILON) +
	                floorf(point.z + EPSILON));
	if (sum % 2 == 0)
		return (pattern.color_a);
	return (pattern.color_b);
}


static t_color	radiant_gradient_pattern_at(t_pat pattern, t_point point)
{
	float	fraction;
	float	distance;
	t_color	col_distance;

	distance = sqrtf(point.x * point.x + point.z * point.z);
	fraction = distance - floorf(distance);
	col_distance = subtraction(pattern.color_b, pattern.color_a);
	return (addition(pattern.color_a, (multiply_color_scalar(col_distance, fraction))));
}

static void	find_object(t_object object, t_matrix *obj_inv)
{
	if (object.id == ELEMENT_SPHERE)
		*obj_inv = object.sp.inv_transform;
	else if (object.id == ELEMENT_PLANE)
		*obj_inv = object.pl.inv_transform;
	else if (object.id == ELEMENT_CYLINDER)
		*obj_inv = object.cy.inv_transform;
	else
		*obj_inv = matrix_identity();
}

t_color	reflected_color(t_info *rt, t_phong_vars vars, int remaining)
{
	t_ray	reflected_ray;
	t_color	reflected_color;

	if (vars.obj->material->reflective == 0)
		return (BLACK);
	if (remaining <= 0)
		return (BLACK);
	reflected_ray = (t_ray){vars.point, vars.reflectv, RAY_REFLECTION};
	reflected_color = rt_color_at(rt, &reflected_ray, remaining - 1);
	return (multiplication(reflected_color, vars.obj->material->reflective));
}

void	prepare_refraction_calculations(t_info *rt, t_intersection *target, float *n1, float *n2)
{
	t_obj_container	container;
	t_object		*object;
	size_t				i;

	container.obj_count = 0;
	*n1 = 1.0f; // MABEY DONT NEED?
	*n2 = 1.0f; // MABEY DONT NEED?
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
		return (container->objs[container->obj_count - 1]->material->refract_ind);
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