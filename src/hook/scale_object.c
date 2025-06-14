/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:39:00 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/11 14:33:03 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static bool	scale_sphere(t_sphere *sp, float factor);
static bool	scale_cylinder(t_cylinder *cy, float factor);
static bool	scale_cone(t_cone *cy, float factor);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Scales the selected object based on keyboard input.
 *
 * Increases or decreases the size of the selected object (sphere, cylinder, 
 * or cone) when the '=' ('+') or '-' key is pressed.
 * If the new size would exceed allowed limits -> operation is canceled.
 * If the object's transform cannot be updated -> program exits with an error.
 *
 * @param rt Pointer to the main program structure.
 * @param obj Pointer to the object to scale.
 * @param key Pointer to the key event data.
 */
void	rt_scale_object(t_info *rt, t_object *obj, mlx_key_data_t *key)
{
	float	factor;

	factor = -0.1f;
	if (key->key == MLX_KEY_EQUAL)
		factor = 0.1f;
	if (ELEMENT_SPHERE == obj->id)
		rt->win.rendered = scale_sphere(&obj->sp, factor);
	else if (ELEMENT_CYLINDER == obj->id)
		rt->win.rendered = scale_cylinder(&obj->cy, factor);
	else if (ELEMENT_CONE == obj->id)
		rt->win.rendered = scale_cone(&obj->co, factor);
	else
		return ;
	if (rt->win.rendered)
		return ;
	if (0 != rt_update_transform(rt, obj, obj->id))
		rt_destroy_exit(rt, ERR_MATRIX_NON_INVERSIBLE);
	rt->win.rendered = false;
}

/* ------------------- Private Function Implementation --------------------- */

static bool	scale_sphere(t_sphere *sp, float factor)
{
	const float	min_limit = MIN_SIZE / 2.0f;
	const float	max_limit = MAX_SIZE / 2.0f;
	float		new_radius;

	factor = 1.0f + factor;
	new_radius = sp->scale * factor;
	if (new_radius < min_limit || new_radius > max_limit)
		return (true);
	sp->scale = new_radius;
	return (false);
}

static bool	scale_cylinder(t_cylinder *cy, float factor)
{
	const float	min_limit = MIN_SIZE / 2.0f;
	const float	max_limit = MAX_SIZE / 2.0f;
	float		new_radius;
	float		new_half_height;

	factor = 1.0f + factor;
	new_radius = cy->scale * factor;
	new_half_height = cy->half_height * factor;
	if (fminf(new_radius, new_half_height) < min_limit)
		return (true);
	if (fmaxf(new_radius, new_half_height) > max_limit)
		return (true);
	cy->scale = new_radius;
	cy->half_height = new_half_height;
	return (false);
}

static bool	scale_cone(t_cone *co, float factor)
{
	const float	min_limit = MIN_SIZE / 2.0f;
	const float	max_limit = MAX_SIZE / 2.0f;
	float		new_radius;
	float		new_height;

	factor = 1.0f + factor;
	new_radius = co->scale * factor;
	new_height = co->height * factor;
	if (new_radius < min_limit || new_radius > max_limit)
		return (true);
	if (new_height < MIN_SIZE || new_height > MAX_SIZE)
		return (true);
	co->scale = new_radius;
	co->height = new_height;
	return (false);
}
