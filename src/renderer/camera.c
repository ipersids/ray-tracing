/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 01:47:44 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/08 11:18:50 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Initializes the camera and renders the scene pixel by pixel.
 *
 * Sets up the camera parameters and iterates over each pixel in the image,
 * casting a ray through each pixel, computing its color, 
 * and drawing it to the image.
 *
 * @param rt Pointer to the main program structure.
 */
void	rt_camera_render(t_info *rt)
{
	uint32_t	px;
	uint32_t	py;
	t_ray		ray;
	t_color		ray_col;
	uint32_t	rgba;

	py = 0;
	rt_camera_init(&rt->camera, &rt->win);
	rt_view_transform(&rt->camera, rt->win.world_up);
	while (py < rt->win.img->height)
	{
		px = 0;
		while (px < rt->win.img->width)
		{
			ray = rt_get_ray(&rt->camera, px, py);
			ray_col = rt_color_at(rt, &ray, MAX_RAY_RECURSION_DEPTH);
			rgba = rt_convert_to_rgba(&ray_col);
			mlx_put_pixel(rt->win.img, px, py, rgba);
			++px;
		}
		++py;
	}
}

/**
 * @brief Initializes camera parameters for rendering.
 *
 * Calculates the camera's half-width, half-height, and pixel size
 * based on the field of view and the aspect ratio of the window.
 *
 * @param cam Pointer to the camera structure.
 * @param win Pointer to the canvas/window structure.
 */
void	rt_camera_init(t_camera *cam, t_canvas *win)
{
	float	half_view;
	float	aspect_ratio;

	half_view = tanf(radians(cam->fov) / 2.0f);
	aspect_ratio = (float)win->width / (float)win->height;
	if (aspect_ratio >= 1.0f)
	{
		cam->half_width = half_view;
		cam->half_height = half_view / aspect_ratio;
	}
	else
	{
		cam->half_width = half_view * aspect_ratio;
		cam->half_height = half_view;
	}
	cam->pixel_size = (cam->half_width * 2.0) / (float)win->width;
}
