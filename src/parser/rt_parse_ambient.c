/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_ambient.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:00:31 by ipersids          #+#    #+#             */
/*   Updated: 2025/04/26 14:50:11 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	get_ration(float *ratio, char *line, char **next);

int	rt_parse_ambient(t_info *rt, char *line)
{
	char	*next;
	int		exit_code;

	next = NULL;
	exit_code = 0;
	while (ft_isspace(*line))
		++line;
	exit_code = get_ration(&rt->ambient.ratio, line, &next);
	if (0 != exit_code)
		return (exit_code);
	line = next;
	while (ft_isspace(*line))
		++line;
	exit_code = rt_parse_color(&rt->ambient.color, line, &next);
	if (0 != exit_code)
		return (exit_code);
	line = next;
	while (ft_isspace(*line))
		++line;
	if ('\0' != *line)
		return (ERR_OBJECT_CONFIG);
	return (0);
}

static int	get_ration(float *ratio, char *line, char **next)
{
	float	res;

	res = 10.0;
	res = (float)ft_strtod(line, next);
	if (line == *next)
		return (ERR_OBJECT_CONFIG);
	if (0.0 > res || 1.0 < res)
		return (ERR_OBJECT_CONFIG_LIMITS);
	*ratio = res;
	return (0);
}
