/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_handle_cursor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:48:52 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/09 16:57:40 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Handles mouse movement events for camera rotation.
 * 
 * When dragging is active, calculates the offset of the cursor,
 * updates `yaw` and `pitch`, clamps pitch to avoid flipping,
 * and updates the camera's forward direction and view transform.
 *
 * @param xpos Current x position of the mouse.
 * @param ypos Current y position of the mouse.
 * @param param Pointer to the main program structure (t_info*).
 */
void	rt_cursor_hook(double xpos, double ypos, void *param)
{
	t_info		*rt;
	t_cursor	*cursor;

	rt = (t_info *)param;
	cursor = &rt->win.cursor;
	if (!cursor->is_camera && !cursor->is_object)
	{
		cursor->last_x = xpos;
		cursor->last_y = ypos;
		return ;
	}
	if (cursor->is_object && mlx_is_key_down(rt->win.mlx, MLX_KEY_LEFT_SHIFT))
	{
		printf("OBJECT pretends to be rotated\n"); // delete
		cursor->last_x = xpos;
		cursor->last_y = ypos;
	}
	else if (cursor->is_object)
		rt_move_object(rt, cursor, xpos, ypos);
	else
		rt_rotate_camera(rt, cursor, xpos, ypos);
	rt->win.rendered = false;
}
