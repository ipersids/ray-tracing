/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bump_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:38:34 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/21 11:04:54 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

/**
 * @brief Checks if the character at the end of the bump map type is valid.
 *
 * Valid end-of-line characters are whitespace, null terminator, or '#'.
 *
 * @param line Pointer to the character after the bump map type.
 * @return true if valid, false otherwise.
 */
static inline bool		is_valid_eol(char *line);

/**
 * @brief Returns the bump map type corresponding to the string in the line.
 * @param line Pointer to the start of the bump map type string.
 * @return The corresponding t_bump_type, or BUMP_MAX if not found.
 */
static t_bump_type	get_bump_map_type(char *line);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Parses a bump map type from the scene description.
 *
 * Sets the bump map type for the current object if a valid type is found.
 * Only valid if IS_BONUS is enabled.
 *
 * @param rt Pointer to the main program structure.
 * @param start Pointer to the current position in the scene line.
 * @return 0 on success, or ERR_BUMP_MAP if the type is invalid.
 */
int	rt_parse_bump_map(t_info *rt, char **start)
{
	t_bump_type	bump_type;

	bump_type = get_bump_map_type(*start);
	if (BUMP_MAX == bump_type)
		return (ERR_BUMP_MAP);
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
	if (ft_strncmp(line, "bump_wall", 9) == 0 && is_valid_eol(&line[9]))
		return (BUMP_WALL);
	return (BUMP_MAX);
}

static inline bool	is_valid_eol(char *line)
{
	return (ft_isspace(*line) || '\0' == (*line) || '#' == (*line));
}
