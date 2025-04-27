/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:49:52 by ipersids          #+#    #+#             */
/*   Updated: 2025/04/27 11:16:48 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	get_fov(int *val, char *line, char **endptr);

int	rt_parse_camera(t_info *rt, char *line)
{
	char	*next;
	int		exit_code;

	exit_code = 0;
	while (ft_isspace(*line))
		++line;
	next = line;
	exit_code = rt_parse_coord(&rt->camera.pos, line, &next, false);
	if (0 != exit_code)
		return (exit_code);
	line = next;
	while (ft_isspace(*line))
		++line;
	exit_code = rt_parse_coord(&rt->camera.dir, line, &next, true);
	if (0 != exit_code)
		return (exit_code);
	line = next;
	while (ft_isspace(*line))
		++line;
	next = line;
	exit_code = get_fov(&rt->camera.fov, line, &next);
	return (exit_code);
}

static int	get_fov(int *val, char *line, char **endptr)
{
	int	fov;

	fov = 360;
	while (ft_isdigit(**endptr))
		(*endptr) += 1;
	if ((*endptr) == line)
		return (ERR_OBJECT_CONFIG);
	fov = ft_atoi(line);
	while (ft_isdigit(**endptr))
		(*endptr) += 1;
	while (ft_isspace(**endptr))
		(*endptr) += 1;
	if ('\0' != (**endptr))
		return (ERR_OBJECT_CONFIG);
	if (0 > fov || 180 < fov)
		return (ERR_OBJECT_CONFIG_LIMITS);
	*val = fov;
	return (0);
}
