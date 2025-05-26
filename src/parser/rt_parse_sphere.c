/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_sphere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:49:23 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/26 10:35:54 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Parse sphere settings from a string.
 * 
 * @param rt Pointer to the ray tracing information structure.
 * @param line The input line containing sphere data.
 * @return int 0 on success, or an error code.
 */
int	rt_parse_sphere(t_info *rt, char *line)
{
	char	*next;
	int		exit_code;
	size_t	i;

	next = NULL;
	exit_code = 0;
	i = rt->n_objs;
	rt->objs[i].id = ELEMENT_SPHERE;
	exit_code = rt_parse_coord(&rt->objs[i].sp.pos, &line, &next, false);
	if (0 != exit_code)
		return (exit_code);
	while (ft_isspace(*line))
		line++;
	exit_code = rt_parse_float(&rt->objs[i].sp.diam, &line, &next);
	if (0 != exit_code)
		return (exit_code);
	if (rt->objs[i].sp.diam > LIMIT_S || rt->objs[i].sp.diam < (2.0 * EPSILON))
		return (ERR_OBJECT_CONFIG_LIMITS);
	rt->objs[i].sp.r = rt->objs[i].sp.diam / 2.0;
	exit_code = rt_parse_color(&rt->objs[i].sp.color, &line, &next);
	if (0 != exit_code)
		return (exit_code);
	exit_code = rt_validate_end_of_line(&line, &next);
	rt->n_objs += 1;
	return (exit_code);
}
