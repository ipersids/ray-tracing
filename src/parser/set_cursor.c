/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cursor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:46:10 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/03 18:21:26 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_set_cursor(t_info *rt)
{
	t_vec3	*forward;

	forward = &rt->camera.forward;
	rt->win.cursor.pitch = asinf(-forward->y) * (180.0f / M_PI);
	rt->win.cursor.yaw = atan2f(forward->x, forward->z) * (180.0f / M_PI);
	while (180.0f < rt->win.cursor.yaw)
		rt->win.cursor.yaw -= 360.0f;
	while (-180.0f > rt->win.cursor.yaw)
		rt->win.cursor.yaw += 360.0f;
	rt->win.cursor.is_first = true;
	rt->win.cursor.is_dragging = false;
	return (0);
}
