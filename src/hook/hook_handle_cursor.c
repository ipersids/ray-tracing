/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_handle_cursor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:48:52 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/11 14:03:21 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Handles mouse movement events for camera and object manipulation.
 * 
 * If neither camera nor object manipulation is active: 
 * 	-> updates the cursor's last position.
 * If object manipulation is active:
 * 	-> calls rt_move_object to move the selected object.
 * If camera manipulation is active:
 * 	-> calls rt_rotate_camera to rotate the camera.
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
	if (cursor->is_object)
		rt_move_object(rt, cursor, xpos, ypos);
	else
		rt_rotate_camera(rt, cursor, xpos, ypos);
}
