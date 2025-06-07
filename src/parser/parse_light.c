/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:51:31 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/08 02:37:09 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Parse light settings from a string.
 * 
 * @param rt Pointer to the ray tracing information structure.
 * @param line The input line containing light data.
 * @return int 0 on success, or an error code.
 */
int	rt_parse_light(t_info *rt, char *line)
{
	char	*next;
	int		exit_code;
	size_t	i;
	float	bright;
	t_color	color;

	next = NULL;
	exit_code = 0;
	i = rt->n_lights;
	rt->n_lights += 1;
	exit_code = rt_parse_coord(&rt->lights[i].pos, &line, &next, false);
	while (ft_isspace(*line))
		++line;
	exit_code = rt_parse_float(&bright, &line, &next);
	if (0 != exit_code)
		return (exit_code);
	if (0.0 > bright || 1.0 < bright)
		return (ERR_OBJECT_CONFIG_LIMITS);
	exit_code = rt_parse_color(&color, &line, &next);
	if (0 != exit_code)
		return (exit_code);
	rt->lights[i].intensity = multiply_color_scalar(color, bright);
	exit_code = rt_validate_end_of_line(&line, &next);
	return (exit_code);
}
