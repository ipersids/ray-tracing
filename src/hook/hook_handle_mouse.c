/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_handle_mouse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:51:57 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/11 14:09:31 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

/**
 * @brief Handles enabling/disabling camera manipulation mode.
 * @param win Pointer to the window structure.
 * @param action Mouse action (MLX_PRESS or MLX_RELEASE).
 */
static void	handle_camera(t_window *win, action_t action);

/**
 * @brief Handles enabling/disabling object manipulation mode.
 * @param rt Pointer to the main program structure.
 * @param win Pointer to the window structure.
 * @param action Mouse action (MLX_PRESS or MLX_RELEASE).
 */
static void	handle_object(t_info *rt, t_window *win, action_t action);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Handles mouse button events and updates cursor state.
 * 
 * - Left mouse button:
 * 	 Enables camera dragging mode (unless object manipulation is active).
 *   When pressed, sets camera manipulation active and disables object.
 *   When released, disables camera manipulation.
 * - Right mouse button:
 * 	 Enables object selection and manipulation (unless camera is active).
 *   When pressed, casts a ray from the mouse position, 
 * 	 finds the closest object under the cursor,
 *   and enables object manipulation if an object is hit.
 *   When released, disables object manipulation.
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
		handle_camera(win, a);
	if (k == MLX_MOUSE_BUTTON_RIGHT && !win->cursor.is_camera)
		handle_object(rt, win, a);
}

/* ------------------- Private Function Implementation --------------------- */

static void	handle_camera(t_window *win, action_t action)
{
	if (action == MLX_PRESS)
	{
		win->cursor.is_camera = true;
		win->cursor.is_object = false;
	}
	else if (action == MLX_RELEASE)
		win->cursor.is_camera = false;
}

static void	handle_object(t_info *rt, t_window *win, action_t action)
{
	t_intersection	*t;
	t_ray			ray;
	int32_t			x;
	int32_t			y;

	x = 0;
	y = 0;
	if (action == MLX_PRESS)
	{
		win->cursor.is_camera = false;
		mlx_get_mouse_pos(win->mlx, &x, &y);
		ray = rt_get_ray(&rt->camera, x, y);
		/// @todo create intersect_world lite ->
		rt_intersect_world(rt, &ray);
		t = find_closest_intersection(rt->ts, rt->n_ts);
		// <- end todo
		if (NULL != t)
		{
			win->cursor.is_object = true;
			win->cursor.obj_to_move = &rt->objs[t->i_object];
		}
	}
	else if (action == MLX_RELEASE)
		win->cursor.is_object = false;
}
