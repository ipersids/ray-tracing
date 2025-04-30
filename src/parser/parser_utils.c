/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 23:54:02 by ipersids          #+#    #+#             */
/*   Updated: 2025/04/30 14:08:09 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "minirt.h"

int	rt_parse_float(float *value, char **startptr, char **endptr)
{
	double	res;

	res = FLT_MAX;
	*endptr = *startptr;
	res = ft_strtod(*startptr, endptr);
	if (*endptr == *startptr)
		return (ERR_OBJECT_CONFIG);
	if (FLT_MAX < res)
		*value = FLT_MAX;
	else if (-FLT_MAX > res)
		*value = -FLT_MAX;
	else
		*value = (float)res;
	*startptr = (*endptr) + 1;
	return (0);
}

int	rt_parse_coord(t_point *pos, char **start, char **endptr, bool is_norm)
{
	int		exit_code;

	exit_code = 0;
	while (ft_isspace(**start))
		++(*start);
	exit_code = rt_parse_float(&pos->x, start, endptr);
	if (0 != exit_code || ',' != **endptr)
		return (ERR_OBJECT_CONFIG);
	if (pos->x > LIMIT_COORD || pos->x < -LIMIT_COORD)
		return (ERR_OBJECT_CONFIG_LIMITS);
	exit_code = rt_parse_float(&pos->y, start, endptr);
	if (0 != exit_code || ',' != **endptr)
		return (ERR_OBJECT_CONFIG);
	if (pos->y > LIMIT_COORD || pos->y < -LIMIT_COORD)
		return (ERR_OBJECT_CONFIG_LIMITS);
	exit_code = rt_parse_float(&pos->z, start, endptr);
	if (0 != exit_code || !('\0' == **endptr || ft_isspace(**endptr)))
		return (ERR_OBJECT_CONFIG);
	if (pos->z > LIMIT_COORD || pos->z < -LIMIT_COORD)
		return (ERR_OBJECT_CONFIG_LIMITS);
	if (is_norm && (0.0 > pos->x || 0.0 > pos->y || 0.0 > pos->z))
		return (ERR_OBJECT_CONFIG_LIMITS);
	if (is_norm && (1.0 < pos->x || 1.0 < pos->y || 1.0 < pos->z))
		return (ERR_OBJECT_CONFIG_LIMITS);
	return (0);
}

int	rt_parse_color(t_color *color, char **start, char **endptr)
{
	int	exit_code;

	exit_code = 0;
	while (ft_isspace(**start))
		++(*start);
	exit_code = rt_parse_float(&color->x, start, endptr);
	if (0 != exit_code || ',' != **endptr)
		return (ERR_OBJECT_CONFIG);
	if (0.0 > color->x || 255.0 < color->x)
		return (ERR_OBJECT_CONFIG_LIMITS);
	exit_code = rt_parse_float(&color->y, start, endptr);
	if (0 != exit_code || ',' != **endptr)
		return (ERR_OBJECT_CONFIG);
	if (0.0 > color->y || 255.0 < color->y)
		return (ERR_OBJECT_CONFIG_LIMITS);
	exit_code = rt_parse_float(&color->z, start, endptr);
	if (0 != exit_code || !('\0' == **endptr || ft_isspace(**endptr)))
		return (ERR_OBJECT_CONFIG);
	if (0.0 > color->z || 255.0 < color->z)
		return (ERR_OBJECT_CONFIG_LIMITS);
	return (0);
}

int	rt_validate_end_of_line(char **startptr, char **endptr)
{
	*endptr = *startptr;
	while (ft_isspace(**startptr))
		++(*startptr);
	if ('\0' != (**startptr))
		return (ERR_OBJECT_CONFIG);
	return (0);
}
