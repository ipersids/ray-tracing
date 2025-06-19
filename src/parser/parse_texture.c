/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:39:52 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/19 13:09:21 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static inline bool		is_valid_eol(char *line);
static t_texture_type	get_texture_type(char *line);

/* --------------------------- Public Functions ---------------------------- */

int	rt_parse_texture(t_info *rt, char **start)
{
	t_texture_type	texture_type;

	texture_type = get_texture_type(*start);
	if (TEXTURE_MAX == texture_type)
		return (ERR_PATTERN);
	rt->objs[rt->n_objs].has_texture = true;
	rt->objs[rt->n_objs].tex_type = texture_type;
	while (ft_isalpha(**start) || '_' == (**start))
		++(*start);
	return (0);
}

/* ------------------- Private Function Implementation --------------------- */

static t_texture_type	get_texture_type(char *line)
{
	if (ft_strncmp(line, "texture_earth", 13) == 0 && is_valid_eol(&line[13]))
		return (TEXTURE_EARTH);
	if (ft_strncmp(line, "texture_mars", 12) == 0 && is_valid_eol(&line[12]))
		return (TEXTURE_MARS);
	if (ft_strncmp(line, "texture_wall", 12) == 0 && is_valid_eol(&line[12]))
		return (TEXTURE_WALL);
	return (TEXTURE_MAX);
}

static inline bool	is_valid_eol(char *line)
{
	return (ft_isspace(*line) || '\0' == (*line) || '#' == (*line));
}
