/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_handle_mouse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:51:57 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/09 13:33:05 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static void	haldle_camera(t_window *win, action_t action);
static void	haldle_object(t_info *rt, t_window *win, action_t action);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Handles mouse button events and updates cursor state.
 * 
 * When the left mouse button is pressed, dragging mode is enabled and the
 * current mouse position is stored. When released, dragging mode is disabled.
 * 
 * @param k Mouse button identifier.
 * @param a Action type (MLX_PRESS or MLX_RELEASE).
 * @param m Key modifiers (unused).
 * @param p Pointer to the main program structure (t_info*).
 */
void	rt_mouse_hook(mouse_key_t k, action_t a, modifier_key_t m, void *p)
{
	t_info		*rt;
	t_window	*win;

	(void)m;
	rt = (t_info *)p;
	win = (t_window *)&rt->win;
	if (k == MLX_MOUSE_BUTTON_LEFT && !win->cursor.is_object)
		haldle_camera(win, a);
	if (k == MLX_MOUSE_BUTTON_RIGHT && !win->cursor.is_camera)
		haldle_object(rt, win, a);
}

/* ------------------- Private Function Implementation --------------------- */

static void	haldle_camera(t_window *win, action_t action)
{
	if (action == MLX_PRESS)
	{
		win->cursor.is_camera = true;
		win->cursor.is_object = false;
	}
	else if (action == MLX_RELEASE)
		win->cursor.is_camera = false;
}

static void	haldle_object(t_info *rt, t_window *win, action_t action)
{
	int32_t	x;
	int32_t	y;

	x = 0;
	y = 0;
	(void)rt;
	(void)win;
	if (action == MLX_PRESS)
	{
		win->cursor.is_camera = false;
		mlx_get_mouse_pos(win->mlx, &x, &y);
		t_ray ray = rt_get_ray(&rt->camera, x, y);
		rt_intersect_world(rt, &ray);
		t_intersection *t = find_closest_intersection(rt->ts, rt->n_ts);
		if (NULL != t)
		{
			win->cursor.is_object = true;
			win->cursor.obj_to_move = &rt->objs[t->i_object];
		}
	}
	else if (action == MLX_RELEASE)
		win->cursor.is_object = false;
}
