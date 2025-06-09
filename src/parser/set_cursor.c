/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cursor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:46:10 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/09 13:31:25 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Sets initial cursor `yaw` and `pitch`.
 * 
 * Computes the `pitch` and `yaw` angles from the camera's forward direction,
 * normalizes the yaw to the range [-180, 180], and resets cursor state flags.
 * 
 * @param rt Pointer to the main program structure (t_info*).
 */
void	rt_set_cursor(t_info *rt)
{
	t_vec3	*forward;

	forward = &rt->camera.forward;
	rt->win.cursor.pitch = asinf(-forward->y) * (180.0f / M_PI);
	if (MAX_PITCH < rt->win.cursor.pitch)
		rt->win.cursor.pitch = MAX_PITCH;
	else if (-MAX_PITCH > rt->win.cursor.pitch)
		rt->win.cursor.pitch = -MAX_PITCH;
	rt->win.cursor.yaw = atan2f(forward->x, forward->z) * (180.0f / M_PI);
	while (180.0f < rt->win.cursor.yaw)
		rt->win.cursor.yaw -= 360.0f;
	while (-180.0f > rt->win.cursor.yaw)
		rt->win.cursor.yaw += 360.0f;
}
