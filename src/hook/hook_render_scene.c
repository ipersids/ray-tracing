/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_render_scene.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reerikai <reerikai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:30:21 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/25 14:33:26 by reerikai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <time.h>

static inline double	get_time_ms(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000.0 + ts.tv_nsec / 1000000.0);
}

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Hook function to render the scene when needed.
 *
 * - Updates the elapsed time using the delta time provided by MLX.
 * - If the window was resized, resizes the image buffer
 *   and resets the resized flag.
 * - If the scene has not been rendered since the last change,
 *   renders the scene, and sets the rendered flag.
 *
 * @param param Pointer to the main program structure (t_info*).
 */
void	rt_render_hook(void *param)
{
	t_info		*rt;
	t_window	*win;
	double		start;
	double		end;

	rt = (t_info *)param;
	win = &rt->win;
	win->elapsed_time += win->mlx->delta_time;
	if (true == win->resized)
	{
		if (!mlx_resize_image(win->img, win->width, win->height))
			rt_destroy_exit(rt, ERR_MLX42);
		win->resized = false;
	}
	if (false == win->rendered)
	{
		start = get_time_ms();
		rt_camera_render(rt);
		end = get_time_ms();
		printf("Render: %s%.1f%s ms (%dx%d)\n", PRINT_RED, end - start,
			PRINT_DEFAULT, rt->win.img->width, rt->win.img->height); // delete
		win->rendered = true;
	}
}
