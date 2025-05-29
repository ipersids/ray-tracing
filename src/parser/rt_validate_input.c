/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_validate_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 00:51:02 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/28 23:58:24 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

/**
 * @brief Validates arguments and file extension then reads file.
 * @param argc The number of arguments passed to the program.
 * @param argv The array of argument strings.
 * @param content A pointer to a pointer to an array for the scene content.
 * @return o in success, otherwise — error code.
 */
static int	validate_args(int argc, char **argv, char ***content);

static int	perform_computations(t_info *rt);

/* --------------------------- Public functions ---------------------------- */

/**
 * @brief Validate input arguments and parse the scene file.
 * 
 * @param argc The number of arguments passed to the program.
 * @param argv The array of argument strings.
 * @param rt Pointer to the ray tracing information structure.
 * @return int 0 on success, or an error code.
 */
int	rt_validate_input(int argc, char **argv, t_info *rt)
{
	int		exit_code;
	char	**content;

	content = NULL;
	exit_code = 0;
	exit_code = validate_args(argc, argv, &content);
	if (0 != exit_code)
		return (exit_code);
	exit_code = rt_parse_scene(rt, content);
	rt_free_arr((void **)content, NULL_TERMINATED_ARR);
	if (0 != exit_code)
		return (exit_code);
	exit_code = perform_computations(rt);
	return (exit_code);
}

/* ------------------- Private function implementation --------------------- */

static int	validate_args(int argc, char **argv, char ***content)
{
	char	*slash;
	char	*name;
	int		name_len;
	int		fd;
	int		exit_code;

	if (2 != argc)
		return (ERR_ARGC);
	name = argv[1];
	slash = ft_strrchr(name, '/');
	if (NULL != slash)
		name = slash + 1;
	name_len = (int)ft_strlen(name) - (int)ft_strlen(EXTENSION);
	if (0 >= name_len || ft_strcmp(&name[name_len], EXTENSION))
		return (ERR_EXTENSION);
	fd = open(argv[1], O_RDONLY);
	if (-1 == fd)
		return (ERR_SYSTEM);
	exit_code = rt_read_scene(fd, content);
	close(fd);
	return (exit_code);
}

static int	perform_computations(t_info *rt)
{
	int	exit_code;

	exit_code = 0;
	exit_code = rt_set_transformations(rt);
	return (exit_code);
}
