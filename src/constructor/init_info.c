/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:47:12 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/08 20:20:47 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

/**
 * @brief Initialize default ambient light settings.
 * @param ambient Pointer to the ambient light structure.
 */
static void	init_ambient(t_color *ambient_intensity);

/**
 * @brief Initialize default camera settings.
 * @param camera Pointer to the camera structure.
 */
static void	init_camera(t_camera *camera);

/**
 * @brief Initializes the window with the necessary properties.
 * @param window A pointer to the `t_window` structure to be initialized.
 */
static void	init_window(t_window *window);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Initialize the ray tracing information structure.
 * @param rt Pointer to the ray tracing information structure.
 */
void	rt_init_info(t_info *rt)
{
	ft_memset(rt, 0, sizeof(t_info));
	init_ambient(&rt->amb_intensity);
	init_camera(&rt->camera);
	init_window(&rt->win);
}

/* ------------------- Private Function Implementation --------------------- */

static void	init_ambient(t_color *ambient_intensity)
{
	const t_color	color = (t_color){1.0f, 1.0f, 1.0f};
	const float		ratio = 0.1f;
	*ambient_intensity = multiplication(color, ratio);
}

static void	init_camera(t_camera *cam)
{
	cam->forward = (t_vec3){0.0f, 0.0f, 1.0f};
	cam->pos = (t_point){0.0f, 0.0f, -100.0f};
	cam->fov = 40.0f;
}

static void	init_window(t_window *window)
{
	window->height = HEIGHT_DEFAULT;
	window->width = WIDTH_DEFAULT;
	window->world_up = (t_vec3){0.0f, 1.0f, 0.0f};
	window->rendered = false;
	window->resized = false;
}
