/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cursor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:46:10 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/03 17:22:12 by ipersids         ###   ########.fr       */
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
	printf("Initialized cursor from camera forward (%.2f, %.2f, %.2f)\n",
        forward->x, forward->y, forward->z);
    printf("Calculated yaw: %.2f°, pitch: %.2f°\n",
		rt->win.cursor.yaw, rt->win.cursor.pitch);
	return (0);
}
