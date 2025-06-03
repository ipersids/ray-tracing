/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_zoom_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:29:31 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/03 20:26:48 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Zoom camera by FOV (Field of View)
 * 
 * Recommended FOV: 45° to 90°
 * Available FOV: 0° to 180°
 * 
 * FOV controls how "wide" the camera can see:
 * - Small FOV (30°): Telephoto lens, zoomed in, narrow view
 * - Medium FOV (60°): Normal lens, natural view  
 * - Large FOV (120°): Wide angle lens, fisheye effect
 * 
 *     FOV = 30° (narrow)        FOV = 90° (wide)
 *         \   /                     \       /
 *          \ /                       \     /
 *           |                         \   /
 *        camera                        \ /
 *                                    camera
 * 
 * @param xdelta The scroll offset along the x-axis
 * @param ydelta The scroll offset along the y-axis.
 * @param param Additional parameter to use inside hook (t_info)
 */
void	rt_scroll_hook(double xdelta, double ydelta, void* param)
{
	t_info	*rt;

	(void)xdelta;
	rt = (t_info *)param;
	rt->camera.fov -= (float)ydelta;
	if (FOV_ZOOM_MIN > rt->camera.fov)
		rt->camera.fov = FOV_ZOOM_MIN;
	else if (FOV_ZOOM_MAX < rt->camera.fov)
		rt->camera.fov = FOV_ZOOM_MAX;
	printf("rt->camera.fov = %f\n", rt->camera.fov);
	rt->win.rendered = false;
}
