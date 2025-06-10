/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_handle_keys.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:52:44 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/10 13:19:27 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Handles key events and dispatches movement/reset.
 * 
 * @param k Key function callback data.
 * @param param Pointer to the main program structure.
 */
void	rt_key_hook(mlx_key_data_t k, void *param)
{
	t_info		*rt;

	rt = (t_info *)param;
	if ((k.key == MLX_KEY_W || k.key == MLX_KEY_S
		|| k.key == MLX_KEY_A || k.key == MLX_KEY_D)
		&& (k.action == MLX_PRESS || k.action == MLX_REPEAT))
		rt_move_camera(rt, &k);
	else if (k.key == MLX_KEY_R && (k.action == MLX_PRESS))
		rt_reset_camera(rt);
}
