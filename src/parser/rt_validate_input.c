/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_validate_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 00:51:02 by ipersids          #+#    #+#             */
/*   Updated: 2025/04/26 15:00:51 by ipersids         ###   ########.fr       */
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

int	rt_validate_input(int argc, char **argv, t_info *rt)
{
	int		exit_code;
	char	**content;

	content = NULL;
	exit_code = validate_args(argc, argv, &content);
	if (0 != exit_code)
		return (exit_code);

	/// @todo parse the scene and validate content
	exit_code = rt_parse_scene(rt, content);
	if (0 != exit_code)
	{
		rt_free_arr((void **)content, NULL_TERMINATED_ARR);
		return (exit_code);
	}
	
	/// @test ->
	if (content) {
		int i = 0;
		for (; content[i] != NULL; i++) {
			ft_printf("Line %d:\t%s\n", i, content[i]); // issue for libft
		}
		rt_free_arr((void **)content, NULL_TERMINATED_ARR);
	} else {
		ft_printf("No data\n");
	}

	printf("A: %f\t%i,%i,%i\n", rt->ambient.ratio, rt->ambient.color.r,
			rt->ambient.color.g, rt->ambient.color.b);
	printf("C: %f,%f,%f\t%f,%f,%f\t%i\n", rt->camera.pos.x, rt->camera.pos.y,
		rt->camera.pos.z, rt->camera.dir.x, rt->camera.dir.y,
		rt->camera.dir.z, rt->camera.fov);
	printf("L: %f,%f,%f\t%f\n", rt->light.pos.x, rt->light.pos.y,
		rt->light.pos.z, rt->light.bright);
	printf("Pointer to objects: %p\n", rt->obj);
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
