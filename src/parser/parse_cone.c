/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 19:32:11 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/21 11:11:01 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static int	parse_radius_and_height(t_info *rt, char **startptr, char **endptr);
static int	parse_direction(t_info *rt, char **line, char **next);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Parses a cone object from the scene description line.
 * 
 * Only valid if IS_BONUS is enabled.
 * 
 * @param rt Pointer to the main program structure.
 * @param line Pointer to the current line in the scene file.
 * @return 0 on success, or an error code on failure.
 */
int	rt_parse_cone(t_info *rt, char *line)
{
	char	*next;
	int		exit_code;
	size_t	i;

	next = NULL;
	i = rt->n_objs;
	rt->objs[i].id = ELEMENT_CONE;
	exit_code = rt_parse_coord(&rt->objs[i].co.pos, &line, &next, false);
	if (0 != exit_code)
		return (exit_code);
	exit_code = parse_direction(rt, &line, &next);
	if (0 != exit_code)
		return (exit_code);
	exit_code = parse_radius_and_height(rt, &line, &next);
	if (0 != exit_code)
		return (exit_code);
	exit_code = rt_parse_color(&rt->objs[i].color, &line, &next);
	if (0 != exit_code)
		return (exit_code);
	if (0 != rt_update_transform(rt, &rt->objs[i], rt->objs[i].id))
		return (ERR_MATRIX_NON_INVERSIBLE);
	exit_code = rt_parse_bonus_settings(rt, &line);
	rt->n_objs += 1;
	return (exit_code);
}

/* ------------------- Private Function Implementation --------------------- */

static int	parse_direction(t_info *rt, char **line, char **next)
{
	int		exit_code;
	size_t	i;

	exit_code = 0;
	i = rt->n_objs;
	exit_code = rt_parse_coord(&rt->objs[i].co.dir, line, next, true);
	if (0 != exit_code)
		return (exit_code);
	if (equal(magnitude(rt->objs[i].co.dir), 0.0f))
		return (ERR_OBJECT_ORIENT_VECTOR);
	rt->objs[i].co.dir = normalize(rt->objs[i].co.dir);
	return (exit_code);
}

static int	parse_radius_and_height(t_info *rt, char **startptr, char **endptr)
{
	int		exit_code;
	size_t	i;

	exit_code = 0;
	i = rt->n_objs;
	while (ft_isspace(**startptr))
		++(*startptr);
	exit_code = rt_parse_float(&rt->objs[i].co.scale, startptr, endptr);
	if (0 != exit_code)
		return (exit_code);
	if (rt->objs[i].co.scale < MIN_SIZE || rt->objs[i].co.scale > MAX_SIZE / 2)
		return (ERR_OBJECT_CONFIG_LIMITS);
	while (ft_isspace(**startptr))
		++(*startptr);
	exit_code = rt_parse_float(&rt->objs[i].co.height, startptr, endptr);
	if (0 != exit_code)
		return (exit_code);
	if (rt->objs[i].co.height < MIN_SIZE || rt->objs[i].co.height > MAX_SIZE)
		return (ERR_OBJECT_CONFIG_LIMITS);
	return (0);
}
