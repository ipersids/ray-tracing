/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_validate_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 00:51:02 by ipersids          #+#    #+#             */
/*   Updated: 2025/04/20 14:03:50 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

/**
 * @brief Validates arguments and file extension then reads file.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The array of argument strings.
 * @param content A pointer to a pointer to an array for the scene content.
 * 
 * @return o in success, otherwise — error code.
 * 
 */
static int	validate_args(int argc, char **argv, char ***content);

/* --------------------------- Public functions ---------------------------- */

int	rt_validate_input(int argc, char **argv)
{
	int		exit_code;
	char	**content;

	content = NULL;
	exit_code = validate_args(argc, argv, &content);
	if (0 != exit_code)
		return (exit_code);

	/// @todo parse the scene and validate content
	
	/// @test ->
	if (content) {
		int i = 0;
		for (; content[i] != NULL; i++) {
			ft_printf("Line %d:\t%s\n", i, content[i]); // issue for libft
		}
		rt_free_arr((void **)content, i);
	} else {
		ft_printf("No data\n");
	}
	/// end <--
	
	return (0);
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
	name_len = (int)ft_strlen(name) - (int)ft_strlen(EXTENTION);
	if (0 >= name_len || ft_strcmp(&name[name_len], EXTENTION))
		return (ERR_EXTENSION);
	fd = open(argv[1], O_RDONLY);
	if (-1 == fd)
		return (ERR_SYSTEM);
	exit_code = rt_read_scene(fd, content);
	close(fd);
	return (exit_code);
}
