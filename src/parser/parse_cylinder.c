/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:35:22 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/05 14:53:13 by ipersids         ###   ########.fr       */
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
 */
static int	parse_diam_and_height(t_info *rt, char **startptr, char **endptr);

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
	exit_code = 0;
	i = rt->n_objs;
	rt->objs[i].id = ELEMENT_CYLINDER;
	exit_code = rt_parse_coord(&rt->objs[i].cy.pos, &line, &next, false);
	if (0 != exit_code)
		return (exit_code);
	exit_code = rt_parse_coord(&rt->objs[i].cy.dir, &line, &next, true);
	if (0 != exit_code)
		return (exit_code);
	rt->objs[i].cy.dir = normalize(rt->objs[i].cy.dir);
	exit_code = parse_diam_and_height(rt, &line, &next);
	if (0 != exit_code)
		return (exit_code);
	exit_code = rt_parse_color(&rt->objs[i].cy.color, &line, &next);
	if (0 != exit_code)
		return (exit_code);
	exit_code = rt_validate_end_of_line(&line, &next);
	rt->n_objs += 1;
	return (exit_code);
}

/* ------------------- Private Function Implementation --------------------- */

static int	parse_diam_and_height(t_info *rt, char **startptr, char **endptr)
{
	int		exit_code;
	size_t	i;

	exit_code = 0;
	i = rt->n_objs;
	while (ft_isspace(**startptr))
		++(*startptr);
	exit_code = rt_parse_float(&rt->objs[i].cy.diam, startptr, endptr);
	if (0 != exit_code)
		return (exit_code);
	if (rt->objs[i].cy.diam > LIMIT_S || rt->objs[i].cy.diam < -LIMIT_S)
		return (ERR_OBJECT_CONFIG_LIMITS);
	while (ft_isspace(**startptr))
		++(*startptr);
	exit_code = rt_parse_float(&rt->objs[i].cy.height, startptr, endptr);
	if (0 != exit_code)
		return (exit_code);
	if (rt->objs[i].cy.height > LIMIT_S || rt->objs[i].cy.height < -LIMIT_S)
		return (ERR_OBJECT_CONFIG_LIMITS);
	rt->objs[i].cy.r = 1.0f;
	rt->objs[i].cy.scale = rt->objs[i].cy.diam / 2.0f;
	rt->objs[i].cy.half_height = rt->objs[i].cy.height / 2.0f;
	return (0);
}
