/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_handle_mouse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:51:57 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/03 23:21:07 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	t_cursor	*cursor;
	int32_t		x;
	int32_t		y;

	(void)m;
	x = 0;
	y = 0;
	rt = (t_info *)p;
	cursor = (t_cursor *)&rt->win.cursor;
	if (k == MLX_MOUSE_BUTTON_LEFT)
	{
		if (a == MLX_PRESS)
		{
			cursor->is_dragging = true;
			mlx_get_mouse_pos(rt->win.mlx, &x, &y);
			cursor->last_x = (float)x;
			cursor->last_y = (float)y;
		}
		else if (a == MLX_RELEASE)
			cursor->is_dragging = false;
	}
}
