/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:39:52 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/21 13:33:09 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

/**
 * @brief Checks if the character at the end of the texture type is valid.
 *
 * Valid end-of-line characters are whitespace, null terminator, or '#'.
 *
 * @param line Pointer to the character after the texture type.
 * @return true if valid, false otherwise.
 */
static inline bool			is_valid_eol(char *line);

/**
 * @brief Returns the texture type corresponding to the string in the line.
 * @param line Pointer to the start of the texture type string.
 * @return The corresponding t_texture_type, or TEXTURE_MAX if not found.
 */
static t_texture_type	get_texture_type(char *line);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Parses a texture type from the scene description.
 *
 * Sets the texture type for the current object if a valid type is found.
 *
 * @param rt Pointer to the main program structure.
 * @param start Pointer to the current position in the scene line.
 * @return 0 on success, or ERR_PATTERN if the type is invalid.
 */
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
	if (ft_strncmp(line, "texture_sun", 11) == 0 && is_valid_eol(&line[11]))
		return (TEXTURE_SUN);
	if (ft_strncmp(line, "texture_mercury", 15) == 0 && is_valid_eol(&line[15]))
		return (TEXTURE_MERCURY);
	if (ft_strncmp(line, "texture_venus", 13) == 0 && is_valid_eol(&line[13]))
		return (TEXTURE_VENUS);
	if (ft_strncmp(line, "texture_earth", 13) == 0 && is_valid_eol(&line[13]))
		return (TEXTURE_EARTH);
	if (ft_strncmp(line, "texture_mars", 12) == 0 && is_valid_eol(&line[12]))
		return (TEXTURE_MARS);
	if (ft_strncmp(line, "texture_jupiter", 15) == 0 && is_valid_eol(&line[15]))
		return (TEXTURE_JUPITER);
	if (ft_strncmp(line, "texture_saturn", 14) == 0 && is_valid_eol(&line[14]))
		return (TEXTURE_SATURN);
	if (ft_strncmp(line, "texture_uranus", 14) == 0 && is_valid_eol(&line[14]))
		return (TEXTURE_URANUS);
	if (ft_strncmp(line, "texture_neptune", 15) == 0 && is_valid_eol(&line[15]))
		return (TEXTURE_NEPTUNE);
	if (ft_strncmp(line, "texture_pluto", 13) == 0 && is_valid_eol(&line[13]))
		return (TEXTURE_PLUTO);
	return (TEXTURE_MAX);
}

static inline bool	is_valid_eol(char *line)
{
	return (ft_isspace(*line) || '\0' == (*line) || '#' == (*line));
}
