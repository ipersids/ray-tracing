/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_close_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 22:19:14 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/09 22:56:50 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Sets the hook for the ESC key to close the window and exit program.
 * @param param Pointer to the t_info* structure.
 */
void	rt_press_esc_hook(void *param)
{
	t_info	*rt;

	rt = (t_info *)param;
	if (mlx_is_key_down(rt->win.mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(rt->win.mlx);
		rt_destroy_exit(rt, EXIT_SUCCESS);
	}
}

/**
 * @brief Sets the hook for the close buttom to terminate window and program.
 * @param param Pointer to the t_info* structure.
 */
void	rt_close_window_hook(void *param)
{
	t_info	*rt;

	rt = (t_info *)param;
	rt_destroy_exit(rt, EXIT_SUCCESS);
}
