/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:58:08 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/11 22:24:16 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

/**
 * @brief Handles saving or restoring camera settings.
 *
 * If update_saved is true or this is the first call, saves the camera's current
 * position, forward vector, and FOV as the reset state. Otherwise, restores the
 * camera's settings from the saved state.
 *
 * @param camera Pointer to the camera structure.
 * @param update_saved If true, save current settings; if false, restore them.
 */
static void	handle_camera_settings(t_camera *camera, bool update_saved);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Resets the camera to its saved/default position, direction, and FOV.
 * @param rt Pointer to the main program structure.
 */
void	rt_reset_camera(t_info *rt)
{
	handle_camera_settings(&rt->camera, false);
	rt_init_cursor(rt);
	rt->win.rendered = false;
}

/**
 * @brief Saves the current camera settings as the reset/default state.
 * @param camera Pointer to the camera structure.
 */
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
