/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_render_scene.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:30:21 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/05 02:04:56 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline double get_time_ms(void) {
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000.0 + ts.tv_nsec / 1000000.0);
}

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
	if (true == win->resized)
	{
		if (!mlx_resize_image(win->img, win->width, win->height))
			rt_destroy_exit(rt, ERR_MLX42);
		win->resized = false;
	}
	if (win->move_elapsed_time <= MOVEMENT_TIMEOUT)
	{
		double start = get_time_ms();
		printf("RENDER_FAST ");
		win->move_elapsed_time += win->mlx->delta_time;
		rt_camera_render(rt, RENDER_HALF_QUALITY);
		double end = get_time_ms();
		printf("Render: %s%.1f%s ms (%dx%d)\n", PRINT_RED, end - start,
			PRINT_DEFAULT, rt->win.img->width, rt->win.img->height);
		printf("win->move_elapsed_time = %f\n", win->move_elapsed_time);
	}
	else if (!win->rendered)
	{
		double start = get_time_ms();
		rt_camera_render(rt, RENDER_FULL_QUALITY);
		double end = get_time_ms();
		printf("Render: %s%.1f%s ms (%dx%d)\n", PRINT_RED, end - start,
			PRINT_DEFAULT, rt->win.img->width, rt->win.img->height);
		win->rendered = true;
	}
}
