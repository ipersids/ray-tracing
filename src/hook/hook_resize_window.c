/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_resize_window.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:54:38 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/01 12:55:58 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Hook function to handle window resize events.
 *
 * @param width The new width of the window.
 * @param height The new height of the window.
 * @param param Pointer to the main program structure (`t_info`).
 */
void	rt_resize_hook(int32_t width, int32_t height, void *param)
{
	t_info	*rt;

	rt = (t_info *)param;
	rt->win.width = width;
	rt->win.height = height;
	rt->win.rendered = false;
	rt->win.resized = true;
}
