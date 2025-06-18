/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bump_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:38:34 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/18 18:15:10 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static inline bool	is_valid_eol(char *line);
static t_bump_type	get_bump_map_type(char *line);

/* --------------------------- Public Functions ---------------------------- */

int	rt_parse_bump_map(t_info *rt, char **start)
{
	t_bump_type	bump_type;

	bump_type = get_bump_map_type(*start);
	if (BUMP_MAX == bump_type)
		return (ERROR_BUMP_MAP);
	rt->objs[rt->n_objs].has_bump_map = true;
	rt->objs[rt->n_objs].bump_type = bump_type;
	while (ft_isalpha(**start) || '_' == (**start))
		++(*start);
	return (0);
}

/* ------------------- Private Function Implementation --------------------- */

static t_bump_type	get_bump_map_type(char *line)
{
	if (ft_strncmp(line, "bump_earth", 10) == 0 && is_valid_eol(&line[10]))
		return (BUMP_EARTH);
	if (ft_strncmp(line, "bump_mars", 9) == 0 && is_valid_eol(&line[9]))
		return (BUMP_MARS);
	return (BUMP_MAX);
}

static inline bool	is_valid_eol(char *line)
{
	return (ft_isspace(*line) || '\0' == (*line) || '#' == (*line));
}
