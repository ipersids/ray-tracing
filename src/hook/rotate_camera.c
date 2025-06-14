/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:40:38 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/11 13:45:02 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	cursor->pitch = clampf(cursor->pitch, -MAX_PITCH_CAMERA, MAX_PITCH_CAMERA);
	direction.x = sin(radians(cursor->yaw)) * cos(radians(cursor->pitch));
	direction.y = -sin(radians(cursor->pitch));
	direction.z = cos(radians(cursor->yaw)) * cos(radians(cursor->pitch));
	rt->camera.forward = normalize(direction);
	if (0 != rt_view_transform(&rt->camera, rt->win.world_up))
	{
		ft_putstr_fd("Camera transform failed (rotation)\n", STDERR_FILENO);
		rt_destroy_exit(rt, ERR_CAMERA_NON_INVERSIBLE);
	}
	rt->win.rendered = false;
}
