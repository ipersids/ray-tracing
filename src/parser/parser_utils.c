/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 23:54:02 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/08 16:11:01 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>		// for float limits — FLT_MAX
#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Parse a float value from a string.
 * 
 * @param value Pointer to store the parsed float.
 * @param startptr Pointer to the start of the string.
 * @param endptr Pointer to a pointer to the character where parsing stopped.
 * @return int 0 on success, or an error code.
 */
int	rt_parse_float(float *value, char **startptr, char **endptr)
{
	double	res;

	res = FLT_MAX;
	*endptr = *startptr;
	res = ft_strtod(*startptr, endptr);
	if (*endptr == *startptr || ft_isspace(**startptr))
		return (ERR_OBJECT_CONFIG);
	if (FLT_MAX < res)
		*value = FLT_MAX;
	else if (-FLT_MAX > res)
		*value = -FLT_MAX;
	else
		*value = (float)res;
	if ('\0' == (**endptr))
		*startptr = (*endptr);
	else
		*startptr = (*endptr) + 1;
	return (0);
}

/**
 * @brief Parse a 3D coordinate from a string.
 * 
 * @param pos Pointer to store the parsed coordinates.
 * @param start Pointer to the start of the string.
 * @param endptr Pointer to a pointer to the character where parsing stopped.
 * @param is_norm Whether the coordinate is normalized.
 * @return int 0 on success, or an error code.
 */
int	rt_parse_coord(t_point *pos, char **start, char **endptr, bool is_norm)
{
	int		exit_code;

	exit_code = 0;
	while (ft_isspace(**start))
		++(*start);
	exit_code = rt_parse_float(&pos->x, start, endptr);
	if (0 != exit_code || ',' != (**endptr))
		return (ERR_OBJECT_CONFIG);
	if (pos->x > LIMIT_COORD || pos->x < -LIMIT_COORD)
		return (ERR_OBJECT_CONFIG_LIMITS);
	exit_code = rt_parse_float(&pos->y, start, endptr);
	if (0 != exit_code || ',' != (**endptr))
		return (ERR_OBJECT_CONFIG);
	if (pos->y > LIMIT_COORD || pos->y < -LIMIT_COORD)
		return (ERR_OBJECT_CONFIG_LIMITS);
	exit_code = rt_parse_float(&pos->z, start, endptr);
	if (0 != exit_code || !('\0' == **endptr || ft_isspace(**endptr)))
		return (ERR_OBJECT_CONFIG);
	if (pos->z > LIMIT_COORD || pos->z < -LIMIT_COORD)
		return (ERR_OBJECT_CONFIG_LIMITS);
	if (is_norm && (-1.0 > pos->x || -1.0 > pos->y || -1.0 > pos->z))
		return (ERR_OBJECT_CONFIG_LIMITS);
	if (is_norm && (1.0 < pos->x || 1.0 < pos->y || 1.0 < pos->z))
		return (ERR_OBJECT_CONFIG_LIMITS);
	return (0);
}

/**
 * @brief Parse a color value from a string.
 * 
 * Colors from the scene file are represented in the RGB [0, 255] range and 
 * will be normalized to fit the [0.0, 1.0] range.
 * 
 * @param color Pointer to store the parsed color.
 * @param start Pointer to the start of the string.
 * @param endptr Pointer to a pointer to the character where parsing stopped.
 * @return int 0 on success, or an error code.
 */
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
	color->x = color->x / 255.0;
	color->y = color->y / 255.0;
	color->z = color->z / 255.0;
	return (0);
}

/**
 * @brief Validate the end of a line in a string.
 * 
 * Allows commented lines with `#` specifier 
 * 
 * @param startptr Pointer to the start of the string.
 * @param endptr Pointer to a pointer to the character where spaces ended.
 * @return int 0 on success, or an error code.
 */
int	rt_validate_end_of_line(char **startptr, char **endptr)
{
	*endptr = *startptr;
	while (ft_isspace(**startptr))
		++(*startptr);
	if ('\0' != (**startptr) && '#' != (**startptr))
		return (ERR_OBJECT_CONFIG);
	return (0);
}
