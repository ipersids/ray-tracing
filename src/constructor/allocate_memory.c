/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:53:41 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/11 20:24:02 by ipersids         ###   ########.fr       */
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
int	rt_allocate_memory(t_counter *cnt, t_info *rt)
{
	if (1 <= cnt->figures)
	{
		rt->objs = ft_calloc(cnt->figures, sizeof(t_object));
		rt->capacity_ts = cnt->figures * 2;
		rt->ts = ft_calloc(rt->capacity_ts, sizeof(t_intersection));
		if (!rt->objs || !rt->ts)
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
