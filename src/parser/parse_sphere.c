/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:49:23 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/11 23:06:38 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static int	parse_radius(t_info *rt, char **line, char **next);

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
	i = rt->n_objs;
	rt->objs[i].id = ELEMENT_SPHERE;
	exit_code = rt_parse_coord(&rt->objs[i].sp.pos, &line, &next, false);
	if (0 != exit_code)
		return (exit_code);
	while (ft_isspace(*line))
		line++;
	exit_code = parse_radius(rt, &line, &next);
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

static int	parse_radius(t_info *rt, char **line, char **next)
{
		int		exit_code;
	size_t	i;

	exit_code = 0;
	i = rt->n_objs;
	exit_code = rt_parse_float(&rt->objs[i].sp.scale, line, next);
	if (0 != exit_code)
		return (exit_code);
	if (rt->objs[i].sp.scale < MIN_SIZE || rt->objs[i].sp.scale > MAX_SIZE)
		return (ERR_OBJECT_CONFIG_LIMITS);
	rt->objs[i].sp.scale = rt->objs[i].sp.scale / 2.0f;
	return (exit_code);
}
