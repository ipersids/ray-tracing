/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:31:14 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/18 17:37:55 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

/**
 * @brief Initializes the MLX window with default settings.
 * @param window Pointer to the window structure to initialize.
 * @return int 0 on success, error code on failure.
 */
static int	init_window(t_window *window);

/**
 * @brief Sets up hooks for handling events in the MLX window.
 * @param rt Pointer to the main program structure.
 */
static void	init_hook(t_info *rt);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Initializes the window for the ray tracer.
 * 
 * It sets up MLX window and image for drawing content of scene 
 * and sets up hooks for handling events in the MLX window.
 * 
 * @param rt Pointer to the main program structure.
 * @return int 0 on success, error code on failure.
 */
int	rt_init_window(t_info *rt)
{
	int	exit_code;

	exit_code = init_window(&rt->win);
	if (0 != exit_code)
		return (exit_code);
	rt->win.img = mlx_new_image(rt->win.mlx, rt->win.width, rt->win.height);
	if (!rt->win.img || mlx_image_to_window(rt->win.mlx, rt->win.img, 0, 0) < 0)
		return (ERR_MLX42);
	exit_code = rt_init_bump_map(&rt->win);
	if (0 != exit_code)
		return (exit_code);
	exit_code = rt_init_texture(&rt->win);
	if (0 != exit_code)
		return (exit_code);
	init_hook(rt);
	return (0);
}

/* ------------------- Private Function Implementation --------------------- */

static int	init_window(t_window *window)
{
	int32_t	width;
	int32_t	height;

	width = WIDTH_DEFAULT;
	height = HEIGHT_DEFAULT;
	window->mlx = mlx_init(WIDTH_DEFAULT, HEIGHT_DEFAULT, NAME, true);
	if (!window->mlx)
		return (ERR_MLX42);
	mlx_get_monitor_size(0, &width, &height);
	height = fmax((float)width / ASPECT_RATIO, 1.0);
	if (window->width > width)
	{
		mlx_set_window_size(window->mlx, width, height);
		window->height = height;
		window->width = width;
	}
	mlx_set_window_limit(window->mlx, WIDTH_MIN, HEIGHT_MIN, width, height);
	return (0);
}

static void	init_hook(t_info *rt)
{
	mlx_key_hook(rt->win.mlx, rt_key_hook, rt);
	mlx_scroll_hook(rt->win.mlx, rt_scroll_hook, rt);
	mlx_cursor_hook(rt->win.mlx, rt_cursor_hook, rt);
	mlx_mouse_hook(rt->win.mlx, rt_mouse_hook, rt);
	mlx_resize_hook(rt->win.mlx, rt_resize_hook, rt);
	mlx_loop_hook(rt->win.mlx, rt_press_esc_hook, rt);
	mlx_loop_hook(rt->win.mlx, rt_render_hook, rt);
	mlx_close_hook(rt->win.mlx, rt_close_window_hook, rt);
	mlx_loop(rt->win.mlx);
}
