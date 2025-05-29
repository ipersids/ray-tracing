/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:47:12 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/30 01:49:12 by ipersids         ###   ########.fr       */
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

/**
 * @brief Initializes the canvas with the necessary properties.
 * @param window A pointer to the `t_canvas` structure to be initialized.
 */
static void	init_canvas(t_canvas *window);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Initialize the ray tracing information structure.
 * @param rt Pointer to the ray tracing information structure.
 */
void	rt_init_info(t_info *rt)
{
	init_ambient(&rt->ambient);
	init_camera(&rt->camera);
	init_canvas(&rt->win);
	rt->objs = NULL;
	rt->n_objs = 0;
	rt->lights = NULL;
	rt->n_lights = 0;
}

/* ------------------- Private Function Implementation --------------------- */

static void	init_ambient(t_ambient_light *amb)
{
	amb->color = DEFAULT_AMBIENT_COLOR;
	amb->ratio = DEFAULT_AMBIENT_RATIO;
}

static void	init_camera(t_camera *cam)
{
	ft_memset(cam, 0, sizeof(t_camera));
	cam->forward = DEFAULT_CAMERA_ORIENTATION;
	cam->pos = DEFAULT_CAMERA_POSITION;
	cam->fov = DEFAULT_CAMERA_FOV;
	cam->transform = matrix_identity();
}

static void	init_canvas(t_canvas *window)
{
	window->mlx = NULL;
	window->height = HEIGHT_DEFAULT;
	window->width = WIDTH_DEFAULT;
	window->img = NULL;
	window->a_ratio = ASPECT_RATIO;
	window->world_up = WORLD_UP;
	window->rendered = false;
	window->resized = false;
	window->elapsed_time = 0;
}
