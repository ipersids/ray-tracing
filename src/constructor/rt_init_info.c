/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:47:12 by ipersids          #+#    #+#             */
/*   Updated: 2025/04/23 16:50:54 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_ambient(t_ambient_light *ambient);
void	init_camera(t_camera *camera);
void	init_light(t_light *light);

void	rt_init_info(t_info *rt)
{
	init_ambient(&rt->ambient);
	init_camera(&rt->camera);
	init_light(&rt->light);
	rt->obj = NULL;
}

void	init_ambient(t_ambient_light *ambient)
{
	ambient->color.r = DEFAULT_AMBIENT_COLOR[R];
	ambient->color.g = DEFAULT_AMBIENT_COLOR[G];
	ambient->color.b = DEFAULT_AMBIENT_COLOR[B];
	ambient->ratio = DEFAULT_AMBIENT_RATIO;
}

void	init_camera(t_camera *camera)
{
	camera->pos.x = DEFAULT_CAMERA_POSITION[X];
	camera->pos.y = DEFAULT_CAMERA_POSITION[Y];
	camera->pos.z = DEFAULT_CAMERA_POSITION[Z];
	camera->dir.x = DEFAULT_CAMERA_DIRECTION[X];
	camera->dir.y = DEFAULT_CAMERA_DIRECTION[Y];
	camera->dir.z = DEFAULT_CAMERA_DIRECTION[Z];
	camera->fov = DEFAULT_CAMERA_FOV;
}

void	init_light(t_light *light)
{
	light->pos.x = DEFAULT_LIGHT_POSITION[X];
	light->pos.y = DEFAULT_LIGHT_POSITION[Y];
	light->pos.z = DEFAULT_LIGHT_POSITION[Z];
	light->bright = DEFAULT_LIGHT_BRIGHTNESS;
}
