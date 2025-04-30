/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:51:31 by ipersids          #+#    #+#             */
/*   Updated: 2025/04/30 11:10:03 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_parse_light(t_info *rt, char *line)
{
	char	*next;
	int		exit_code;
	size_t	i;

	next = NULL;
	exit_code = 0;
	i = rt->n_lights;
	exit_code = rt_parse_coord(&rt->lights[i].pos, &line, &next, false);
	while (ft_isspace(*line))
		++line;
	exit_code = rt_parse_float(&rt->lights[i].bright, &line, &next);
	if (0 != exit_code)
		return (exit_code);
	if (0.0 > rt->lights[i].bright || 1.0 < rt->lights[i].bright)
		return (ERR_OBJECT_CONFIG_LIMITS);
	exit_code = rt_parse_color(&rt->lights[i].color, &line, &next);
	if (0 != exit_code)
		return (exit_code);
	rt->n_lights += 1;
	exit_code = rt_validate_end_of_line(&line, &next);
	return (exit_code);
}
