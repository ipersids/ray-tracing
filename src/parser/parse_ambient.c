/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:00:31 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/12 12:59:25 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Parse ambient light settings from a string.
 * 
 * @param rt Pointer to the ray tracing information structure.
 * @param line The input line containing ambient light data.
 * @return int 0 on success, or an error code.
 */
int	rt_parse_ambient(t_info *rt, char *line)
{
	char	*next;
	int		exit_code;
	float	ratio;
	t_color	color;

	next = NULL;
	exit_code = 0;
	while (ft_isspace(*line))
		++line;
	exit_code = rt_parse_float(&ratio, &line, &next);
	if (0 != exit_code || 0 == ft_isspace(*next))
		return (ERR_OBJECT_CONFIG);
	if (0.0 > ratio || 1.0 < ratio)
		return (ERR_OBJECT_CONFIG_LIMITS);
	exit_code = rt_parse_color(&color, &line, &next);
	if (0 != exit_code)
		return (exit_code);
	rt->amb_intensity = multiply_color_scalar(
			color, ratio);
	exit_code = rt_validate_end_of_line(&line);
	return (exit_code);
}
