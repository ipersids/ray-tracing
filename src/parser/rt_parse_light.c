/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:51:31 by ipersids          #+#    #+#             */
/*   Updated: 2025/04/29 15:45:26 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	get_brightness(float *val, char *line, char **next);

int	rt_parse_light(t_info *rt, char *line)
{
	char	*next;
	int		exit_code;

	exit_code = 0;
	while (ft_isspace(*line))
		++line;
	next = line;
	exit_code = rt_parse_coord(&rt->light.pos, line, &next, false);
	line = next;
	while (ft_isspace(*line))
		++line;
	exit_code = get_brightness(&rt->light.bright, line, &next);
	if (0 != exit_code)
		return (exit_code);
	line = next;
	while (ft_isspace(*line))
		++line;
	exit_code = rt_parse_color(&rt->light.color, line, &next);
	if (0 != exit_code)
		return (exit_code);
	while (ft_isspace(*next))
		++next;
	if ('\0' != *next)
		return (ERR_OBJECT_CONFIG);
	return (0);
}

static int	get_brightness(float *val, char *line, char **next)
{
	float	res;

	res = 10.0;
	res = (float)ft_strtod(line, next);
	if (line == *next)
		return (ERR_OBJECT_CONFIG);
	if (0.0 > res || 1.0 < res)
		return (ERR_OBJECT_CONFIG_LIMITS);
	*val = res;
	return (0);
}
