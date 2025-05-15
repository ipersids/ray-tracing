/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 01:47:44 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/16 00:38:02 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	camera_init(t_camera *cam, t_canvas *win);

void	rt_camera_render(t_info *rt)
{
	uint32_t	px;
	uint32_t	py;
	t_ray		ray;
	t_color		ray_color;
	uint32_t	rgba;

	py = 0;
	camera_init(&rt->camera, &rt->win);
	debug_print_camera(&rt->camera); /// @todo delete
	debug_print_world(&rt->win); /// @todo delete
	while (py < rt->win.img->height)
	{
		px = 0;
		while (px < rt->win.img->width)
		{
			ray = rt_get_ray(&rt->camera, px, py);
			ray_color = rt_get_ray_color(&ray);
			rgba = rt_convert_to_rgba(&ray_color);
			mlx_put_pixel(rt->win.img, px, py, rgba);
			++px;
		}
		++py;
	}
}

static void	camera_init(t_camera *cam, t_canvas *win)
{
	t_vec3	vp_center;

	cam->right = cross_product(cam->forward, WORLD_UP);
	cam->up = cross_product(cam->right, cam->forward);
	cam->vport_h = 2.0f * tan((cam->fov * M_PI / 180.0f) / 2.0f) * cam->focal_len;
	cam->vport_w = cam->vport_h * ((float)win->img->width / win->img->height);
	cam->vport_u = multiplication(cam->right, cam->vport_w);
	cam->vport_v = multiplication(cam->up, -cam->vport_h);
	cam->px_delta_u = division(cam->vport_u, (float)win->img->width);
	cam->px_delta_v = division(cam->vport_v, (float)win->img->height);
	vp_center = addition(cam->pos, multiplication(cam->forward, cam->focal_len));
	cam->vport_upleft = subtractation(
		subtractation(vp_center, division(cam->vport_u, 2.0f)),
		division(cam->vport_v, 2.0f)
	);
	cam->px00_loc = addition(
        cam->vport_upleft,
        addition(
            multiplication(cam->px_delta_u, 0.5f),
            multiplication(cam->px_delta_v, 0.5f)
        )
    );
}
