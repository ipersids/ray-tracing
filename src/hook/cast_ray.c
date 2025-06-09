/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 02:56:08 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/09 03:43:24 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>		// for float limits — FLT_MAX
#include "minirt.h"

static t_point	project_position(const t_point *pos, const t_ray *ray);

t_point	rt_calculate_movement(t_info *rt, t_point pos, float dx, float dy)
{
	t_ray		ray[2];
	t_point		point[2];
	t_vec3		move;
	t_cursor	*cur;

	cur = &rt->win.cursor;
	ray[PREVIOUS] = rt_get_ray(&rt->camera, cur->last_x, cur->last_y);
	ray[CURRENT] = rt_get_ray(&rt->camera, cur->last_x - dx, cur->last_y - dy);
	point[PREVIOUS] = project_position(&pos, &ray[PREVIOUS]);
	point[CURRENT] = project_position(&pos, &ray[CURRENT]);
	move = subtraction(point[CURRENT], point[PREVIOUS]);
	return (addition(pos, negation(move)));
}

static t_point	project_position(const t_point *pos, const t_ray *ray)
{
	const float	limiter = 0.1f;
	t_point		point;
	float		t;

	point = subtraction(*pos, ray->orig);
	t = dot_product(point, ray->dir) / dot_product(ray->dir, ray->dir);
	if (t < limiter)
		t = limiter;
	return (addition(ray->orig, multiplication(ray->dir, t)));
}
