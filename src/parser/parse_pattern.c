/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pattern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:37:00 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/12 17:48:22 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static inline bool	is_valid_eol(char *line);
static t_pattype	get_pattern_type(char *line);

/* --------------------------- Public Functions ---------------------------- */

int	rt_parse_pattern(t_info *rt, char **start)
{
	t_pattype	p_type;

	p_type = get_pattern_type(*start);
	if (PATTERN_MAX == p_type)
		return (ERROR_PATTERN);
	rt->objs[rt->n_objs].pattern = &rt->patterns[p_type];
	rt->objs[rt->n_objs].has_pattern = true;
	while (ft_isalpha(**start) || '_' == (**start))
		++(*start);
	return (0);
}

/* ------------------- Private Function Implementation --------------------- */

static t_pattype	get_pattern_type(char *line)
{
	if (ft_strncmp(line, "stripe", 6) == 0 && is_valid_eol(&line[6]))
		return (PATTERN_STRIPE);
	// if (ft_strncmp(line, "ring", 4) == 0 && is_valid_eol(&line[4]))
	// 	return (PATTERN_RING);
	if (ft_strncmp(line, "gradient", 8) == 0 && is_valid_eol(&line[8]))
		return (PATTERN_GRADIENT);
	if (ft_strncmp(line, "checker", 7) == 0 && is_valid_eol(&line[7]))
		return (PATTERN_CHECKER);
	// if (ft_strncmp(line, "radiant_gradient", 16) == 0 && is_valid_eol(&line[16]))
	// 	return (PATTERN_RADIANT_GRADIENT);
	return (PATTERN_MAX);
}

static inline bool	is_valid_eol(char *line)
{
	return (ft_isspace(*line) || '\0' == (*line) || '#' == (*line));
}