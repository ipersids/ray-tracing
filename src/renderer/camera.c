/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 01:47:44 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/28 14:35:00 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Initializes the camera and renders the scene pixel by pixel.
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
	debug_print_camera(&rt->camera); /// @todo delete
	debug_print_world(&rt->win); /// @todo delete
	
	while (py < rt->win.img->height)
	{
		px = 0;
		while (px < rt->win.img->width)
		{
			ray = rt_get_ray(&rt->camera, px, py);
			ray_col = rt_color_at(rt, &ray);
			rgba = rt_convert_to_rgba(&ray_col);
			mlx_put_pixel(rt->win.img, px, py, rgba);
			++px;
		}
		++py;
	}
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Initializes the camera's viewport and related vectors.
 *
 * - `cam->right`: unit direction vector pointing right across the viewport.
 * - `cam->up`: unit vector pointing up from the camera.
 * - `cam->vport_h`: physical height of the viewport.
 * - `cam->vport_w`: physical width of the viewport.
 * - `cam->vport_u`: vector from left to right across the entire viewport.
 * - `cam->vport_v`: full vertical vector going down across the viewport.
 * - `cam->px_delta_u`: 3D vector step per pixel horizontally.
 * - `cam->px_delta_v`: 3D vector step per pixel vertically.
 * - `vp_center`: the center of the viewport, positioned in front of the camera.
 * - `cam->vport_upleft`: corner of the first pixel.
 * - `cam->px00_loc`: position of the top-left pixel center.
 *
 * forward assumed to be normalized
 * 1 degree = 𝜋/180 radians
 * suffixes: u = horizontal, v = vertical
 *
 * @param cam Pointer to the camera structure.
 * @param win Pointer to the canvas structure.
 */
// static void	camera_init(t_camera *cam, t_canvas *win)
// {
// 	t_vec3	vp_center;

// 	cam->right = normalize(cross_product(cam->forward, win->world_up));
// 	cam->true_up = cross_product(cam->right, cam->forward);
// 	cam->vport_h = 2.0f * tanf((cam->fov * M_PI / 180.0f) / 2.0f)
// 		* cam->focal_len;
// 	cam->vport_w = cam->vport_h * ((float)win->img->width / win->img->height);
// 	cam->vport_u = multiplication(cam->right, cam->vport_w);
// 	cam->vport_v = multiplication(cam->true_up, -cam->vport_h);
// 	cam->px_delta_u = division(cam->vport_u, (float)win->img->width);
// 	cam->px_delta_v = division(cam->vport_v, (float)win->img->height);
// 	vp_center = addition(
// 			cam->pos, multiplication(cam->forward, cam->focal_len));
// 	cam->vport_upleft = subtraction(
// 			subtraction(vp_center, division(cam->vport_u, 2.0f)),
// 			division(cam->vport_v, 2.0f)
// 			);
// 	cam->px00_loc = addition(
// 			cam->vport_upleft,
// 			addition(
// 				multiplication(cam->px_delta_u, 0.5f),
// 				multiplication(cam->px_delta_v, 0.5f)
// 				)
// 			);
// }

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
