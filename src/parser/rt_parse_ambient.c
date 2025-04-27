/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_ambient.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:00:31 by ipersids          #+#    #+#             */
/*   Updated: 2025/04/25 19:52:24 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_parse_ambient(t_info *rt, char *line)
{
	char	*next;
	float	ratio;

	next = NULL;
	ratio = 10.0;
	while (ft_isspace(*line))
		++line;
	ratio = (float)ft_strtod(line, &next);
	if (line == next || 0.0 > ratio || 1.0 < ratio)
		return (ERR_OBJECT_CONFIG);
	rt->ambient.ratio = ratio;
	line = next;
	while (ft_isspace(*line))
		++line;
	if (0 != rt_get_color(&rt->ambient.color, line, &next))
		return (ERR_OBJECT_CONFIG);
	line = next;
	while (ft_isspace(*line))
		++line;
	if ('\0' != *line)
		return (ERR_OBJECT_CONFIG);
	return (0);
}
