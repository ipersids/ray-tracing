/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_rotate_camera.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:48:52 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/03 19:17:14 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	handle_rotation(t_info *rt, t_cursor *cursor);

// void mlx_mouse_hook(mlx_t* mlx, mlx_mousefunc func, void* param)

void	rt_cursor_hook(double xpos, double ypos, void *param)
{
	t_info		*rt;
	t_cursor	*cursor;

	rt = (t_info *)param;
	cursor = &rt->win.cursor;
	if (!cursor->is_dragging)
	{
		cursor->last_x = xpos;
		cursor->last_y = ypos;
		return ;
	}
	if (cursor->is_first)
	{
		cursor->last_x = xpos;
		cursor->last_y = ypos;
		cursor->is_first = false;
		return ;
	}
	cursor->xoffset = xpos - cursor->last_x;
	cursor->yoffset = ypos - cursor->last_y;
	cursor->last_x = xpos;
	cursor->last_y = ypos;
	handle_rotation(rt, cursor);
	rt->win.rendered = false;
}

static void	handle_rotation(t_info *rt, t_cursor *cursor)
{
	t_vec3		direction;
	
	cursor->xoffset *= CURSOR_SENSITIVITY;
	cursor->yoffset *= CURSOR_SENSITIVITY;
	cursor->yaw += cursor->xoffset;
	cursor->pitch += cursor->yoffset;
	if (60.0f < cursor->pitch)
		cursor->pitch = 60.0f;
	else if (-60.0f > cursor->pitch)
		cursor->pitch = -60.0f;
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
