#include "minirt.h"

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
