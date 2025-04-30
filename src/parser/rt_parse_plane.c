/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:40:19 by ipersids          #+#    #+#             */
/*   Updated: 2025/04/30 19:44:24 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_parse_plane(t_info *rt, char *line)
{
	char	*next;
	int		exit_code;
	size_t	i;

	next = NULL;
	exit_code = 0;
	i = rt->n_objs;
	rt->objs[i].id = ELEMENT_PLANE;
	exit_code = rt_parse_coord(&rt->objs[i].pl.pos, &line, &next, false);
	if (0 != exit_code)
		return (exit_code);
	exit_code = rt_parse_coord(&rt->objs[i].pl.dir, &line, &next, true);
	if (0 != exit_code)
		return (exit_code);
	exit_code = rt_parse_color(&rt->objs[i].pl.color, &line, &next);
	if (0 != exit_code)
		return (exit_code);
	exit_code = rt_validate_end_of_line(&line, &next);
	rt->n_objs += 1;
	return (exit_code);
}
