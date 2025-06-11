/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_handle_keys.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:52:44 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/11 14:04:58 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Handles keyboard events for camera and object manipulation.
 *
 * If object manipulation is active and WASD is pressed:
 * 	-> rotates the selected object.
 * If WASD is pressed (and not manipulating an object):
 * 	-> moves the camera.
 * If 'R' is pressed:
 * 	-> resets the camera to its default position and orientation.
 * If '-' or '=' ('+') is pressed while manipulating an object:
 * 	-> scales the selected object.
 *
 * @param k Key function callback data (mlx_key_data_t).
 * @param param Pointer to the main program structure (t_info*).
 */
void	rt_key_hook(mlx_key_data_t k, void *param)
{
	t_info		*rt;

	rt = (t_info *)param;
	if (rt->win.cursor.is_object && (k.key == MLX_KEY_W || k.key == MLX_KEY_S
			|| k.key == MLX_KEY_A || k.key == MLX_KEY_D)
		&& (k.action == MLX_PRESS || k.action == MLX_REPEAT))
		rt_rotate_object(rt, rt->win.cursor.obj_to_move, &k);
	else if ((k.key == MLX_KEY_W || k.key == MLX_KEY_S
			|| k.key == MLX_KEY_A || k.key == MLX_KEY_D)
		&& (k.action == MLX_PRESS || k.action == MLX_REPEAT))
		rt_move_camera(rt, &k);
	else if (k.key == MLX_KEY_R && (k.action == MLX_PRESS))
		rt_reset_camera(rt);
	else if ((k.key == MLX_KEY_MINUS || k.key == MLX_KEY_EQUAL)
		&& k.action == MLX_PRESS && rt->win.cursor.is_object)
		rt_scale_object(rt, rt->win.cursor.obj_to_move, &k);
}
