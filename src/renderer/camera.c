/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 01:47:44 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/13 11:59:27 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_camera_render(t_info *rt)
{
	uint32_t	px;
	uint32_t	py;
	t_ray		ray;
	t_color		ray_color;
	uint32_t	rgba;

	py = 0;
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
