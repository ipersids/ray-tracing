/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_movement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 02:56:08 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/09 21:07:56 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static t_point	project_position(const t_point *pos, const t_ray *ray);

/* --------------------------- Public Functions ---------------------------- */

t_point	rt_get_ray_based_move(t_info *rt, t_point pos, float dx, float dy)
{
	t_ray		ray[2];
	t_point		point[2];
	t_vec3		move;
	t_cursor	*cur;

	cur = &rt->win.cursor;
	ray[0] = rt_get_ray(&rt->camera, cur->last_x - dx, cur->last_y - dy);
	ray[1] = rt_get_ray(&rt->camera, cur->last_x, cur->last_y);
	point[0] = project_position(&pos, &ray[0]);
	point[1] = project_position(&pos, &ray[1]);
	move = subtraction(point[1], point[0]);
	return (addition(pos, move));
}

t_point	rt_get_depth_based_move(t_info *rt, t_point pos, float dy)
{
	t_vec3		move;

	move = (t_vec3){0.0f, 0.0f, -dy * CURSOR_SENSITIVITY};
	move = matrix_multiply_vector(rt->camera.inv_transform, move);
	return (addition(pos, move));
}

/* ------------------- Private Function Implementation --------------------- */

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
