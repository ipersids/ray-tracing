/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:47:12 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/01 01:18:16 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

/**
 * @brief Initialize default ambient light settings.
 * @param ambient Pointer to the ambient light structure.
 */
static void	init_ambient(t_ambient_light *ambient);

/**
 * @brief Initialize default camera settings.
 * @param camera Pointer to the camera structure.
 */
static void	init_camera(t_camera *camera);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Initialize the ray tracing information structure.
 * @param rt Pointer to the ray tracing information structure.
 */
void	rt_init_info(t_info *rt)
{
	init_ambient(&rt->ambient);
	init_camera(&rt->camera);
	rt->objs = NULL;
	rt->n_objs = 0;
	rt->lights = NULL;
	rt->n_lights = 0;
}

/* ------------------- Private Function Implementation --------------------- */

static void	init_ambient(t_ambient_light *ambient)
{
	ambient->color.x = DEFAULT_AMBIENT_COLOR_R;
	ambient->color.y = DEFAULT_AMBIENT_COLOR_G;
	ambient->color.z = DEFAULT_AMBIENT_COLOR_B;
	ambient->ratio = DEFAULT_AMBIENT_RATIO;
}

static void	init_camera(t_camera *camera)
{
	camera->pos.x = DEFAULT_CAMERA_POSITION_X;
	camera->pos.y = DEFAULT_CAMERA_POSITION_Y;
	camera->pos.z = DEFAULT_CAMERA_POSITION_Z;
	camera->dir.x = DEFAULT_CAMERA_DIRECTION_X;
	camera->dir.y = DEFAULT_CAMERA_DIRECTION_Y;
	camera->dir.z = DEFAULT_CAMERA_DIRECTION_Z;
	camera->fov = DEFAULT_CAMERA_FOV;
}
