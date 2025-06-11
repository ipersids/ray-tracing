/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:35:22 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/11 23:06:49 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

/**
 * @brief Parse the diameter and height of a cylinder.
 * 
 * @param rt Pointer to the ray tracing information structure.
 * @param startptr Pointer to the start of the string.
 * @param endptr Pointer to a pointer to the character where parsing stopped.
 * @return int 0 on success, or an error code.
 * @note could not be negative or approximately equal zero (less then EPSILON)
 */
static int	parse_diam_and_height(t_info *rt, char **startptr, char **endptr);

static int	parse_direction(t_info *rt, char **line, char **next);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Parse cylinder settings from a string.
 * 
 * @param rt Pointer to the ray tracing information structure.
 * @param line The input line containing cylinder data.
 * @return int 0 on success, or an error code.
 */
int	rt_parse_cylinder(t_info *rt, char *line)
{
	char	*next;
	int		exit_code;
	size_t	i;

	next = NULL;
	i = rt->n_objs;
	rt->objs[i].id = ELEMENT_CYLINDER;
	exit_code = rt_parse_coord(&rt->objs[i].cy.pos, &line, &next, false);
	if (0 != exit_code)
		return (exit_code);
	exit_code = parse_direction(rt, &line, &next);
	if (0 != exit_code)
		return (exit_code);
	exit_code = parse_diam_and_height(rt, &line, &next);
	if (0 != exit_code)
		return (exit_code);
	exit_code = rt_parse_color(&rt->objs[i].color, &line, &next);
	if (0 != exit_code)
		return (exit_code);
	if (0 != rt_update_transform(rt, &rt->objs[i], rt->objs[i].id))
		return (ERR_MATRIX_NON_INVERSIBLE);
	exit_code = rt_validate_end_of_line(&line, &next);
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
	exit_code = rt_parse_coord(&rt->objs[i].cy.dir, line, next, true);
	if (0 != exit_code)
		return (exit_code);
	if (equal(magnitude(rt->objs[i].cy.dir), 0.0f))
		return (ERR_OBJECT_ORIENT_VECTOR);
	rt->objs[i].cy.dir = normalize(rt->objs[i].cy.dir);
	return (exit_code);
}

static int	parse_diam_and_height(t_info *rt, char **startptr, char **endptr)
{
	int		exit_code;
	size_t	i;
	float	max_limit;

	exit_code = 0;
	max_limit = MAX_SIZE / 2.0f;
	i = rt->n_objs;
	while (ft_isspace(**startptr))
		++(*startptr);
	exit_code = rt_parse_float(&rt->objs[i].cy.scale, startptr, endptr);
	if (0 != exit_code)
		return (exit_code);
	rt->objs[i].cy.scale = rt->objs[i].cy.scale / 2.0f;
	if (rt->objs[i].cy.scale < MIN_SIZE || rt->objs[i].cy.scale > max_limit)
		return (ERR_OBJECT_CONFIG_LIMITS);
	while (ft_isspace(**startptr))
		++(*startptr);
	exit_code = rt_parse_float(&rt->objs[i].cy.half_height, startptr, endptr);
	if (0 != exit_code)
		return (exit_code);
	rt->objs[i].cy.half_height = rt->objs[i].cy.half_height / 2.0f;
	if (rt->objs[i].cy.half_height < MIN_SIZE
		|| rt->objs[i].cy.half_height > max_limit)
		return (ERR_OBJECT_CONFIG_LIMITS);
	return (0);
}
