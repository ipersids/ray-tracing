/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 02:35:17 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/10 13:27:13 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Handles key events and dispatches movement/reset.
 * 
 * Implements WASD-style camera movement for the ray tracer:
 * Direction depends on where camera is looking
 * 
 *      W (Forward)
 *          ↑
 *          |
 *   A ←----●----→ D
 * (Left)   |    (Right)
 *          ↓
 *      S (Backward)
 *
 * ● = Camera position
 *
 * R - Reset camera to initial position and orientation
 * 
 * @param k Key function callback data.
 * @param param Pointer to the main program structure.
 */
void	rt_move_camera(t_info *rt, mlx_key_data_t *key)
{
	t_vec3	move_to;
	t_vec3	left;

	if ((key->key == MLX_KEY_W || key->key == MLX_KEY_S))
		move_to = multiplication(rt->camera.forward, CAMERA_SPEED);
	else if ((key->key == MLX_KEY_A || key->key == MLX_KEY_D))
	{
		left = cross_product(rt->camera.forward, rt->win.world_up);
		move_to = multiplication(normalize(left), CAMERA_SPEED / 2.0f);
	}
	if (key->key == MLX_KEY_W || key->key == MLX_KEY_A)
		rt->camera.pos = addition(rt->camera.pos, move_to);
	else if (key->key == MLX_KEY_S || key->key == MLX_KEY_D)
		rt->camera.pos = subtraction(rt->camera.pos, move_to);
	if (0 != rt_view_transform(&rt->camera, rt->win.world_up))
	{
		ft_putstr_fd("Camera transform failed (walking)\n", STDERR_FILENO);
		rt_destroy_exit(rt, ERR_CAMERA_NON_INVERSIBLE);
	}
	rt->win.rendered = false;
}

/**
 * @brief Applies the calculated rotation to the camera.
 *
 * @param rt Pointer to the main program structure (t_info*).
 * @param cursor Pointer to the cursor state structure (t_cursor*).
 * @param x Current x position of the mouse.
 * @param y Current y position of the mouse.
 * @note Exits the program if the camera transform fails.
 */
void	rt_rotate_camera(t_info *rt, t_cursor *cursor, double x, double y)
{
	t_vec3	direction;
	float	xoffset;
	float	yoffset;

	xoffset = x - cursor->last_x;
	yoffset = y - cursor->last_y;
	cursor->last_x = x;
	cursor->last_y = y;
	xoffset *= CURSOR_SENSITIVITY;
	yoffset *= CURSOR_SENSITIVITY;
	cursor->yaw += xoffset;
	cursor->pitch += yoffset;
	if (MAX_PITCH < cursor->pitch)
		cursor->pitch = MAX_PITCH;
	else if (-MAX_PITCH > cursor->pitch)
		cursor->pitch = -MAX_PITCH;
	direction.x = sin(radians(cursor->yaw)) * cos(radians(cursor->pitch));
	direction.y = -sin(radians(cursor->pitch));
	direction.z = cos(radians(cursor->yaw)) * cos(radians(cursor->pitch));
	rt->camera.forward = normalize(direction);
	if (0 != rt_view_transform(&rt->camera, rt->win.world_up))
	{
		ft_putstr_fd("Camera transform failed (rotation)\n", STDERR_FILENO);
		rt_destroy_exit(rt, ERR_CAMERA_NON_INVERSIBLE);
	}
}
