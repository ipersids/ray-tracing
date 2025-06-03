/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_follow_cursor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:48:52 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/03 17:46:23 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_cursor_hook(double xpos, double ypos, void *param)
{
	t_info		*rt;
	t_cursor	*cursor;
	t_vec3		direction;

	rt = (t_info *)param;
	cursor = &rt->win.cursor;
	if (cursor->is_first)
	{
		cursor->last_x = xpos;
		cursor->last_y = ypos;
		cursor->is_first = false;
	}
	cursor->xoffset = xpos - cursor->last_x;
	cursor->yoffset = ypos - cursor->last_y;
	cursor->last_x = xpos;
	cursor->last_y = ypos;
	cursor->xoffset *= CURSOR_SENSITIVITY;
	cursor->yoffset *= CURSOR_SENSITIVITY;
	cursor->yaw += cursor->xoffset;
	cursor->pitch += cursor->yoffset;
	if (89.0f < cursor->pitch)
		cursor->pitch = 89.0f;
	else if (-89.0f > cursor->pitch)
		cursor->pitch = -89.0f;
	direction.x = sin(radians(cursor->yaw)) * cos(radians(cursor->pitch));
	direction.y = -sin(radians(cursor->pitch));
	direction.z = cos(radians(cursor->yaw)) * cos(radians(cursor->pitch));
	rt->camera.forward = normalize(direction);
	if (0 != rt_view_transform(&rt->camera, rt->win.world_up))
		rt_destroy_exit(rt, ERR_CAMERA_NON_INVERSIBLE);
	printf("xpos = %f, ypos = %f\n", xpos, ypos);
	printf("yaw = %f, pitch = %f\n", cursor->yaw, cursor->pitch);
	printf("direction: (%f, %f, %f)\n", direction.x, direction.y, direction.z);
	rt->win.rendered = false;
}
