/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pattern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 10:21:09 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/21 11:07:43 by ipersids         ###   ########.fr       */
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
 * @brief Returns the pattern type corresponding to the string in the line.
 * @param line Pointer to the start of the pattern type string.
 * @return The corresponding t_pattype, or PATTERN_MAX if not found.
 */
static t_pattype	get_pattern_type(char *line);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Parses a pattern type from the scene description.
 *
 * Sets the pattern for the current object if a valid type is found.
 * Only valid if IS_BONUS is enabled.
 * 
 * @param rt Pointer to the main program structure.
 * @param start Pointer to the current position in the scene line.
 * @return 0 on success, or ERR_PATTERN if the type is invalid.
 */
int	rt_parse_pattern(t_info *rt, char **start)
{
	t_pattype	p_type;

	p_type = get_pattern_type(*start);
	if (PATTERN_MAX == p_type)
		return (ERR_PATTERN);
	if (PATTERN_DEFAULT != p_type)
	{
		rt->objs[rt->n_objs].pattern = &rt->patterns[p_type];
		rt->objs[rt->n_objs].has_pattern = true;
	}
	while (ft_isalpha(**start) || '_' == (**start))
		++(*start);
	return (0);
}

/* ------------------- Private Function Implementation -------------------- */

static t_pattype	get_pattern_type(char *line)
{
	if (ft_strncmp(line, "default", 7) == 0 && is_valid_eol(&line[7]))
		return (PATTERN_DEFAULT);
	if (ft_strncmp(line, "stripe", 6) == 0 && is_valid_eol(&line[6]))
		return (PATTERN_STRIPE);
	if (ft_strncmp(line, "gradient", 8) == 0 && is_valid_eol(&line[8]))
		return (PATTERN_GRADIENT);
	if (ft_strncmp(line, "checker", 7) == 0 && is_valid_eol(&line[7]))
		return (PATTERN_CHECKER);
	return (PATTERN_MAX);
}

static inline bool	is_valid_eol(char *line)
{
	return (ft_isspace(*line) || '\0' == (*line) || '#' == (*line));
}
