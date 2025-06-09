/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 02:48:21 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/09 03:27:57 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_move_object(t_info *rt, t_cursor *cursor, double x, double y)
{
	float	xoffset;
	float	yoffset;
	t_point	*pos;
	
	(void)rt;
	xoffset = x - cursor->last_x;
	yoffset = y - cursor->last_y;
	cursor->last_x = x;
	cursor->last_y = y;
	if (ELEMENT_SPHERE == cursor->obj_to_move->id)
	{
		pos = &cursor->obj_to_move->sp.pos;
		*pos = rt_calculate_movement(rt, *pos, xoffset, yoffset);
		if (0 != rt_sphere_transform(&cursor->obj_to_move->sp))
            rt_destroy_exit(rt, ERR_MATRIX_NON_INVERSIBLE);
	}
}
