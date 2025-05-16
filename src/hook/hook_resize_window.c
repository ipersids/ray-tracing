/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_resize_window.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:54:38 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/16 20:42:04 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_resize_hook(int32_t width, int32_t height, void* param)
{
	t_info	*rt;

	rt = (t_info *)param;
	rt->win.a_ratio = (float)width / (float)height;
	rt->win.width = width;
	rt->win.height = height;
	rt->win.rendered = false;
	rt->win.resized = true;
}
