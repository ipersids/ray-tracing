/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:50:51 by ipersids          #+#    #+#             */
/*   Updated: 2025/04/25 19:52:29 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_get_color(t_color *color, char *start, char **endptr)
{
	*endptr = start;
	while (ft_isdigit(**endptr))
		(*endptr) += 1;
	if (*endptr == start || ',' != **endptr)
		return (ERR_OBJECT_CONFIG);
	color->r = ft_atoi(start);
	if (0 > color->r || 255 < color->r)
		return (ERR_OBJECT_CONFIG);
	start = ++(*endptr);
	while (ft_isdigit(**endptr))
		(*endptr) += 1;
	if (*endptr == start || ',' != **endptr)
		return (ERR_OBJECT_CONFIG);
	color->g = ft_atoi(start);
	if (0 > color->g || 255 < color->g)
		return (ERR_OBJECT_CONFIG);
	start = ++(*endptr);
	while (ft_isdigit(**endptr))
		(*endptr) += 1;
	if (*endptr == start)
		return (ERR_OBJECT_CONFIG);
	color->b = ft_atoi(start);
	if (0 > color->b || 255 < color->b)
		return (ERR_OBJECT_CONFIG);
	return (0);
}
