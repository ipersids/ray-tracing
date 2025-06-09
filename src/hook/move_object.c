/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 02:48:21 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/09 13:08:39 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_move_object(t_info *rt, t_cursor *cursor, double x, double y)
{
	float	xoffset;
	float	yoffset;
	int		exit_code;
	
	exit_code = 0;
	xoffset = x - cursor->last_x;
	yoffset = y - cursor->last_y;
	cursor->last_x = x;
	cursor->last_y = y;
	exit_code = rt_perform_movement(rt, cursor->obj_to_move, xoffset, yoffset);
	if (0 != exit_code)
	{
		ft_putstr_fd("Object movement fails:\n", STDERR_FILENO);
		rt_destroy_exit(rt, exit_code);
	}
}
