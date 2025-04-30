/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:53:41 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/01 01:19:25 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Allocate memory for objects and lights in the ray tracing structure.
 * 
 * @param cnt Pointer to the counter structure.
 * @param rt Pointer to the ray tracing information structure.
 * @return int Returns 0 on success, or ERR_SYSTEM on memory allocation failure.
 */
int	rt_init_objects(t_counter *cnt, t_info *rt)
{
	if (1 <= cnt->figures)
	{
		rt->objs = ft_calloc(cnt->figures, sizeof(t_object));
		if (!rt->objs)
			return (ERR_SYSTEM);
	}
	if (1 <= cnt->lights)
	{
		rt->lights = ft_calloc(cnt->lights, sizeof(t_object));
		if (!rt->lights)
			return (ERR_SYSTEM);
	}
	return (0);
}
