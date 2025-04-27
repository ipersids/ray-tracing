/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_coord.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:53:51 by ipersids          #+#    #+#             */
/*   Updated: 2025/04/27 11:17:25 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "minirt.h"

static int	get_coord(float *val, double coord, char *start, char **endptr);

int	rt_parse_coord(t_point *pos, char *start, char **endptr, bool is_norm)
{
	double	val;
	int		exit_code;

	*endptr = start;
	val = FLT_MAX;
	exit_code = 0;
	exit_code = get_coord(&pos->x, val, start, endptr);
	if (0 != exit_code)
		return (exit_code);
	start = *endptr;
	exit_code = get_coord(&pos->y, val, start, endptr);
	if (0 != exit_code)
		return (exit_code);
	start = *endptr;
	val = ft_strtod(start, endptr);
	if ((*endptr) == start)
		return (ERR_OBJECT_CONFIG);
	if (val > LIMIT_COORD || val < -LIMIT_COORD)
		return (ERR_OBJECT_CONFIG_LIMITS);
	pos->z = (float)val;
	if (is_norm && (0.0 > pos->x || 0.0 > pos->y || 0.0 > pos->z))
		return (ERR_OBJECT_CONFIG_LIMITS);
	if (is_norm && (1.0 < pos->x || 1.0 < pos->y || 1.0 < pos->z))
		return (ERR_OBJECT_CONFIG_LIMITS);
	return (0);
}

static int	get_coord(float *val, double coord, char *start, char **endptr)
{
	coord = ft_strtod(start, endptr);
	if ((*endptr) == start || ',' != **endptr || '\0' == **endptr)
		return (ERR_OBJECT_CONFIG);
	start = ++(*endptr);
	if (0 == ft_isdigit(*start))
		return (ERR_OBJECT_CONFIG);
	if (coord > LIMIT_COORD || coord < -LIMIT_COORD)
		return (ERR_OBJECT_CONFIG_LIMITS);
	*val = (float)coord;
	return (0);
}
