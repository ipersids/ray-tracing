/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 02:56:08 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/09 13:11:02 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static t_point	project_position(const t_point *pos, const t_ray *ray);

/* --------------------------- Public Functions ---------------------------- */

int	rt_perform_movement(t_info *rt, t_object *obj, double dx, double dy)
{
	t_point	*pos;
	int		exit_code;
	
	pos = NULL;
	exit_code = 0;
	if (ELEMENT_SPHERE == obj->id)
		pos = &obj->sp.pos;
	else if (ELEMENT_PLANE == obj->id)
		pos = &obj->pl.pos;
	else if (ELEMENT_CYLINDER == obj->id)
		pos = &obj->cy.pos;
	else if (IS_BONUS && ELEMENT_CONE == obj->id)
		pos = &obj->co.pos;
	if (NULL != pos)
	{
		*pos = rt_calculate_movement(rt, *pos, dx, dy);
		exit_code = rt_update_transform(rt, obj, obj->id);
	}
	return (exit_code);
}

/* ------------------- Private Function Implementation --------------------- */

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
	move.z *= Z_DRIFT_DAMPING;
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
