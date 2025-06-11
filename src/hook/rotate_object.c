/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:41:56 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/11 13:44:38 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	perform_rotation(t_info *rt, t_vec3 *dir, mlx_key_data_t *key);
static void	update_direction(t_vec3 *dir, float dyaw, float dpitch);

void	rt_rotate_object(t_info *rt, t_object *obj, mlx_key_data_t *key)
{
	t_vec3	*dir;
	int		exit_code;

	if (ELEMENT_CYLINDER == obj->id)
		dir = &obj->cy.dir;
	else if (ELEMENT_PLANE == obj->id)
		dir = &obj->pl.dir;
	else if (IS_BONUS && ELEMENT_CONE == obj->id)
		dir = &obj->co.dir;
	else
		return ;
	exit_code = perform_rotation(rt, dir, key);
	if (0 != exit_code)
	{
		ft_putstr_fd("Object transform fails (rotation):\n", STDERR_FILENO);
		rt_destroy_exit(rt, exit_code);
	}
	rt->win.rendered = false;
}

static int	perform_rotation(t_info *rt, t_vec3 *dir, mlx_key_data_t *key)
{
	t_object	*obj;
	int			exit_code;

	obj = rt->win.cursor.obj_to_move;
	exit_code = 0;
	if (key->key == MLX_KEY_W)
		update_direction(dir, 0.0f, -ROTATION_STEP);
	else if (key->key == MLX_KEY_S)
		update_direction(dir, 0.0f, ROTATION_STEP);
	else if (key->key == MLX_KEY_A)
		update_direction(dir, -ROTATION_STEP, 0.0f);
	else if (key->key == MLX_KEY_D)
		update_direction(dir, ROTATION_STEP, 0.0f);
	exit_code = rt_update_transform(rt, obj, obj->id);
	return (exit_code);
}

static void	update_direction(t_vec3 *dir, float yaw_delta, float pitch_delta)
{
	float	yaw;
	float	pitch;
	t_vec3	direction;

	pitch = (asin(-dir->y) * 180.0f / M_PI) + pitch_delta;
	yaw = (atan2(dir->x, dir->z) * 180.0f / M_PI) + yaw_delta;
	pitch = clampf(pitch, -MAX_PITCH_OBJECT, MAX_PITCH_OBJECT);
	direction.x = sin(radians(yaw)) * cos(radians(pitch));
	direction.y = -sin(radians(pitch));
	direction.z = cos(radians(yaw)) * cos(radians(pitch));
	debug_print_vector("DIR before: ", *dir);
	debug_print_vector("DIR after: ", direction);
	*dir = normalize(direction);
}
