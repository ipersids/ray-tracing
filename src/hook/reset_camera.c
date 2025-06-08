/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:58:08 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/08 12:43:27 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static void	handle_camera_settings(t_camera *camera, bool update_saved);

/* --------------------------- Public Functions ---------------------------- */

void	rt_reset_camera(t_info *rt)
{
	handle_camera_settings(&rt->camera, false);
	rt_set_cursor(rt);
	rt->win.rendered = false;
}

void	rt_save_camera_settings(t_camera *camera)
{
	handle_camera_settings(camera, true);
}

/* ------------------- Private Function Implementation --------------------- */

static void	handle_camera_settings(t_camera *camera, bool update_saved)
{
	static bool		is_first_call = true;
	static t_point	reset_pos;
	static t_vec3	reset_forward;
	static float	reset_fov;

	if (!camera)
		return ;
	if (is_first_call || update_saved)
	{
		is_first_call = false;
		reset_pos = camera->pos;
		reset_forward = camera->forward;
		reset_fov = camera->fov;
		return ;
	}
	camera->pos = reset_pos;
	camera->forward = reset_forward;
	camera->fov = reset_fov;
}
