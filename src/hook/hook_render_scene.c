/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_render_scene.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:30:21 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/16 20:59:22 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Hook function to render the scene at a fixed frame rate.
 * 
 * 1. Update elapsed time using the delta time provided by MLX.
 * 2. Render the scene if enough time has passed (based on FPS) and
 *		- if window was resized 
 *		- or if scene has been changed
 *	
 * @param param Pointer to the main program structure (`t_info`).
 */
void	rt_render_hook(void *param)
{
	t_info		*rt;
	t_canvas	*win;

	rt = (t_info *)param;
	win = &rt->win;
	win->elapsed_time += win->mlx->delta_time;
	if (win->elapsed_time >= FPS)
	{
		win->elapsed_time -= FPS;
		if (true == win->resized)
		{
			if (!mlx_resize_image(win->img, win->width, win->height))
				rt_destroy_exit(rt, ERR_MLX42);
			win->resized = false;
		}
		if (false == win->rendered)
		{
			rt_camera_render(rt);
			win->rendered = true;
		}
	}
}
