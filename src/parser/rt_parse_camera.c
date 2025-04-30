/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:49:52 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/01 01:29:48 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Parse camera settings from a string.
 * 
 * @param rt Pointer to the ray tracing information structure.
 * @param line The input line containing camera data.
 * @return int 0 on success, or an error code.
 */
int	rt_parse_camera(t_info *rt, char *line)
{
	char	*next;
	int		exit_code;

	next = NULL;
	exit_code = 0;
	exit_code = rt_parse_coord(&rt->camera.pos, &line, &next, false);
	if (0 != exit_code)
		return (exit_code);
	exit_code = rt_parse_coord(&rt->camera.dir, &line, &next, true);
	if (0 != exit_code)
		return (exit_code);
	while (ft_isspace(*line))
		++line;
	exit_code = rt_parse_float(&rt->camera.fov, &line, &next);
	if (0 != exit_code || 0 != rt_validate_end_of_line(&line, &next))
		return (ERR_OBJECT_CONFIG);
	if (0.0 > rt->camera.fov || 180.0 < rt->camera.fov)
		return (ERR_OBJECT_CONFIG_LIMITS);
	return (0);
}
