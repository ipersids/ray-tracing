/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:49:27 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/21 11:07:19 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

/**
 * @brief Checks if the character at the end of the material type is valid.
 *
 * Valid end-of-line characters are whitespace, null terminator, or '#'.
 *
 * @param line Pointer to the character after the material type.
 * @return true if valid, false otherwise.
 */
static inline bool		is_valid_eol(char *line);

/**
 * @brief Returns the material type corresponding to the string in the line.
 * @param line Pointer to the start of the material type string.
 * @return The corresponding t_mtype, or MATERIAL_MAX if not found.
 */
static t_mtype		get_material_type(char *line);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Parses a material type from the scene description.
 * 
 * Only valid if IS_BONUS is enabled.
 * 
 * @param rt Pointer to the main program structure.
 * @param start Pointer to the current position in the scene line.
 * @return 0 on success, or ERR_MATERIAL if the type is invalid.
 */
int	rt_parse_material(t_info *rt, char **start)
{
	t_mtype	m_type;

	m_type = get_material_type(*start);
	if (MATERIAL_MAX == m_type)
		return (ERR_MATERIAL);
	rt->objs[rt->n_objs].material = &rt->materials[m_type];
	while (ft_isalpha(**start) || '_' == (**start))
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
