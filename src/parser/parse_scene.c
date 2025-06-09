/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:58:48 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/09 17:17:30 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

/**
 * @brief Get the type of object from a line.
 * @param line The input line containing object data.
 * @return t_type The type of the object.
 */
static t_type	get_object_type(char *line);

/**
 * @brief Validate object types and count their occurrences.
 * @param cnt Pointer to the counter structure.
 * @param scene Array of strings representing the scene.
 * @return int 0 on success, or an error code.
 */
static int		validate_object_type(t_counter *cnt, char **scene);

/**
 * @brief Parse a single line of the scene.
 * @param rt Pointer to the ray tracing information structure.
 * @param line The input line to parse.
 * @return int 0 on success, or an error code.
 */
static int		parse_line(t_info *rt, char *line);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Parse the entire scene from an array of strings.
 * 
 * @param rt Pointer to the ray tracing information structure.
 * @param scene Array of strings representing the scene.
 * @return int 0 on success, or an error code.
 */
int	rt_parse_scene(t_info *rt, char **scene)
{
	int			exit_code;
	t_counter	cnt;

	if (!scene || !(*scene))
		return (ERROR_EMPTY_SCENE);
	ft_memset(&cnt, 0, sizeof(cnt));
	exit_code = validate_object_type(&cnt, scene);
	if (0 != exit_code)
		return (exit_code);
	exit_code = rt_init_objects(&cnt, rt);
	if (0 != exit_code)
		return (exit_code);
	while (NULL != (*scene))
	{
		exit_code = parse_line(rt, *scene);
		if (0 != exit_code)
		{
			ft_putstr_fd(PRINT_PURPLE"Line: "PRINT_DEFAULT, STDERR_FILENO);
			ft_putstr_fd((*scene), STDERR_FILENO);
			ft_putchar_fd('\n', STDERR_FILENO);
			return (exit_code);
		}
		++scene;
	}
	return (exit_code);
}

/* ------------------- Private Function Implementation --------------------- */

static t_type	get_object_type(char *line)
{
	while (0 != ft_isspace(*line))
		++line;
	if (ft_strncmp(line, "A", 1) == 0 && ft_isspace(line[1]))
		return (ELEMENT_AMBIENT);
	if (ft_strncmp(line, "C", 1) == 0 && ft_isspace(line[1]))
		return (ELEMENT_CAMERA);
	if (ft_strncmp(line, "L", 1) == 0 && ft_isspace(line[1]))
		return (ELEMENT_LIGHT);
	if (ft_strncmp(line, "sp", 2) == 0 && ft_isspace(line[2]))
		return (ELEMENT_SPHERE);
	if (ft_strncmp(line, "pl", 2) == 0 && ft_isspace(line[2]))
		return (ELEMENT_PLANE);
	if (ft_strncmp(line, "cy", 2) == 0 && ft_isspace(line[2]))
		return (ELEMENT_CYLINDER);
	if (IS_BONUS && ft_strncmp(line, "co", 2) == 0 && ft_isspace(line[2]))
		return (ELEMENT_CONE);
	return (ELEMENT_UNKNOWN);
}

static int	validate_object_type(t_counter *cnt, char **scene)
{
	int		i;
	t_type	type;

	i = 0;
	while (scene[i] != NULL)
	{
		type = get_object_type(scene[i]);
		if (ELEMENT_AMBIENT == type)
			cnt->ambient += 1;
		else if (ELEMENT_CAMERA == type)
			cnt->camera += 1;
		else if (ELEMENT_LIGHT == type)
			cnt->lights += 1;
		else if (ELEMENT_UNKNOWN != type)
			cnt->figures += 1;
		else
			return (ERR_OBJECT_TYPE);
		if (1 < cnt->ambient || 1 < cnt->camera)
			return (ERR_OBJECT_AMOUNT);
		if (!IS_BONUS && 1 < cnt->lights)
			return (ERR_OBJECT_AMOUNT);
		++i;
	}
	return (0);
}

static int	parse_line(t_info *rt, char *line)
{
	t_type	type;
	int		exit_code;

	exit_code = 0;
	while (0 != ft_isspace(*line))
		++line;
	type = get_object_type(line);
	if (ELEMENT_AMBIENT == type)
		exit_code = rt_parse_ambient(rt, line + 1);
	else if (ELEMENT_CAMERA == type)
		exit_code = rt_parse_camera(rt, line + 1);
	else if (ELEMENT_LIGHT == type)
		exit_code = rt_parse_light(rt, line + 1);
	else if (ELEMENT_CYLINDER == type)
		exit_code = rt_parse_cylinder(rt, line + 2);
	else if (IS_BONUS && ELEMENT_CONE == type)
		exit_code = rt_parse_cone(rt, line + 2);
	else if (ELEMENT_PLANE == type)
		exit_code = rt_parse_plane(rt, line + 2);
	else if (ELEMENT_SPHERE == type)
		exit_code = rt_parse_sphere(rt, line + 2);
	else
		exit_code = ERR_OBJECT_TYPE;
	return (exit_code);
}
