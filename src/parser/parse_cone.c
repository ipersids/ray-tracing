/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 19:32:11 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/06 19:55:32 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static int	parse_diam_and_height(t_info *rt, char **startptr, char **endptr);

/* --------------------------- Public Functions ---------------------------- */

int	rt_parse_cone(t_info *rt, char *line)
{
	char	*next;
	int		exit_code;
	size_t	i;

	printf("HERE");
	next = NULL;
	exit_code = 0;
	i = rt->n_objs;
	rt->objs[i].id = ELEMENT_CONE;
	exit_code = rt_parse_coord(&rt->objs[i].co.pos, &line, &next, false);
	if (0 != exit_code)
		return (exit_code);
	exit_code = rt_parse_coord(&rt->objs[i].co.dir, &line, &next, true);
	if (0 != exit_code)
		return (exit_code);
	rt->objs[i].co.dir = normalize(rt->objs[i].co.dir);
	exit_code = parse_diam_and_height(rt, &line, &next);
	if (0 != exit_code)
		return (exit_code);
	exit_code = rt_parse_color(&rt->objs[i].co.color, &line, &next);
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
	exit_code = rt_parse_float(&rt->objs[i].co.scale, startptr, endptr);
	if (0 != exit_code)
		return (exit_code);
	if (rt->objs[i].co.scale > LIMIT_S || rt->objs[i].co.scale < -LIMIT_S)
		return (ERR_OBJECT_CONFIG_LIMITS);
	while (ft_isspace(**startptr))
		++(*startptr);
	exit_code = rt_parse_float(&rt->objs[i].co.height, startptr, endptr);
	if (0 != exit_code)
		return (exit_code);
	if (rt->objs[i].co.height > LIMIT_S || rt->objs[i].co.height < -LIMIT_S)
		return (ERR_OBJECT_CONFIG_LIMITS);
	rt->objs[i].co.scale = rt->objs[i].co.scale / 2.0f;;
	return (0);
}
