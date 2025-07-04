/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:40:19 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/12 13:14:46 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Parse plane settings from a string.
 * 
 * @param rt Pointer to the ray tracing information structure.
 * @param line The input line containing plane data.
 * @return int 0 on success, or an error code.
 */
int	rt_parse_plane(t_info *rt, char *line)
{
	char	*next;
	int		exit_code;
	size_t	i;

	next = NULL;
	i = rt->n_objs;
	rt->objs[i].id = ELEMENT_PLANE;
	exit_code = rt_parse_coord(&rt->objs[i].pl.pos, &line, &next, false);
	if (0 != exit_code)
		return (exit_code);
	exit_code = rt_parse_coord(&rt->objs[i].pl.dir, &line, &next, true);
	if (0 != exit_code)
		return (exit_code);
	if (equal(magnitude(rt->objs[i].pl.dir), 0.0f))
		return (ERR_OBJECT_ORIENT_VECTOR);
	rt->objs[i].pl.dir = normalize(rt->objs[i].pl.dir);
	exit_code = rt_parse_color(&rt->objs[i].color, &line, &next);
	if (0 != exit_code)
		return (exit_code);
	if (0 != rt_update_transform(rt, &rt->objs[i], rt->objs[i].id))
		return (ERR_MATRIX_NON_INVERSIBLE);
	exit_code = rt_parse_bonus_settings(rt, &line);
	rt->n_objs += 1;
	return (exit_code);
}
