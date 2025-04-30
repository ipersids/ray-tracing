/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_ambient.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:00:31 by ipersids          #+#    #+#             */
/*   Updated: 2025/04/30 10:52:13 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_parse_ambient(t_info *rt, char *line)
{
	char	*next;
	int		exit_code;

	next = NULL;
	exit_code = 0;
	while (ft_isspace(*line))
		++line;
	exit_code = rt_parse_float(&rt->ambient.ratio, &line, &next);
	if (0 != exit_code || 0 == ft_isspace(*next))
		return (ERR_OBJECT_CONFIG);
	if (0.0 > rt->ambient.ratio || 1.0 < rt->ambient.ratio)
		return (ERR_OBJECT_CONFIG_LIMITS);
	exit_code = rt_parse_color(&rt->ambient.color, &line, &next);
	if (0 != exit_code)
		return (exit_code);
	exit_code = rt_validate_end_of_line(&line, &next);
	return (exit_code);
}
