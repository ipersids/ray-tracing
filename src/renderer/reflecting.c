/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflecting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reerikai <reerikai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:25:22 by reerikai          #+#    #+#             */
/*   Updated: 2025/06/23 14:25:23 by reerikai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	reflected_color(t_info *rt, t_phong_vars vars, int remaining)
{
	t_ray	reflected_ray;
	t_color	reflected_color;

	if (vars.obj->material->reflective == 0)
		return ((t_color){0.0f, 0.0f, 0.0f});
	if (remaining <= 0)
		return ((t_color){0.0f, 0.0f, 0.0f});
	reflected_ray = (t_ray){vars.point, vars.reflectv, RAY_REFLECTION};
	reflected_color = rt_color_at(rt, &reflected_ray, remaining - 1);
	return (multiplication(reflected_color, vars.obj->material->reflective));
}
