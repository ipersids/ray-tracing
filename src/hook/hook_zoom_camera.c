/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_zoom_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:29:31 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/03 19:42:31 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_scroll_hook(double xdelta, double ydelta, void* param)
{
	t_info	*rt;
	t_vec3	move_to;

	(void)xdelta;
	rt = (t_info *)param;
	move_to = multiplication(rt->camera.forward, ydelta * CAMERA_ZOOM_SPEED);
	rt->camera.pos = addition(rt->camera.pos, move_to);
	if (0 != rt_view_transform(&rt->camera, rt->win.world_up))
	{
		ft_putstr_fd("Camera transform failed (zoom)\n", STDERR_FILENO);
		rt_destroy_exit(rt, ERR_CAMERA_NON_INVERSIBLE);
	}
	rt->win.rendered = false;
}
