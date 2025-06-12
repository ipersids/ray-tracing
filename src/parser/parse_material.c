/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:49:27 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/12 13:19:46 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static inline bool	is_valid_eol(char *line);
static t_mtype		get_material_type(char *line);

/* --------------------------- Public Functions ---------------------------- */

int	rt_parse_material(t_info *rt, char **start)
{
	t_mtype	m_type;

	m_type = get_material_type(*start);
	if (MATERIAL_MAX == m_type)
		return (ERROR_MATERIAL);
	rt->objs[rt->n_objs].material = &rt->materials[m_type];
	while (ft_isalpha(**start) || ft_isspace(**start))
		++(*start);
	return (0);
}

/* ------------------- Private Function Implementation --------------------- */

static t_mtype	get_material_type(char *line)
{
	if (ft_strncmp(line, "default", 7) == 0 && is_valid_eol(&line[7]))
		return (MATERIAL_DEFAULT);
	if (ft_strncmp(line, "lambertian", 10) == 0 && is_valid_eol(&line[10]))
		return (MATERIAL_LAMBERTIAN);
	if (ft_strncmp(line, "rusted_metall", 13) == 0 && is_valid_eol(&line[13]))
		return (MATERIAL_RUSTED_METALL);
	if (ft_strncmp(line, "metall", 6) == 0 && is_valid_eol(&line[6]))
		return (MATERIAL_METALL);
	if (ft_strncmp(line, "glass", 5) == 0 && is_valid_eol(&line[5]))
		return (MATERIAL_GLASS);
	if (ft_strncmp(line, "diamond", 7) == 0 && is_valid_eol(&line[7]))
		return (MATERIAL_DIAMOND);
	if (ft_strncmp(line, "plastic", 7) == 0 && is_valid_eol(&line[7]))
		return (MATERIAL_PLASTIC);
	if (ft_strncmp(line, "ceramic", 7) == 0 && is_valid_eol(&line[7]))
		return (MATERIAL_CERAMIC);
	if (ft_strncmp(line, "mirror", 6) == 0 && is_valid_eol(&line[6]))
		return (MATERIAL_MIRROR);
	if (ft_strncmp(line, "water", 5) == 0 && is_valid_eol(&line[5]))
		return (MATERIAL_WATER);
	if (ft_strncmp(line, "ice", 3) == 0 && is_valid_eol(&line[3]))
		return (MATERIAL_ICE);
	return (MATERIAL_MAX);
}

static inline bool	is_valid_eol(char *line)
{
	return (ft_isspace(*line) || '\0' == (*line) || '#' == (*line));
}