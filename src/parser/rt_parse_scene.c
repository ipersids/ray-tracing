/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:58:48 by ipersids          #+#    #+#             */
/*   Updated: 2025/04/25 16:27:02 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	validate_object_type(t_counter *cnt, char **scene);
static bool	is_figure(char *line);

int	rt_parse_scene(t_info *rt, char **scene)
{
	int			exit_code;
	t_counter	cnt;

	ft_memset(&cnt, 0, sizeof(cnt));
	printf("%d\n", cnt.ambient);
	exit_code = validate_object_type(&cnt, scene);
	if (0 != exit_code)
		return (exit_code);
	rt->obj = malloc(cnt.figures * sizeof(t_object));
	if (!rt->obj)
		return (ERR_SYSTEM);
	return (0);
}

static int	validate_object_type(t_counter *cnt, char **scene)
{
	int	i;

	i = -1;
	while (scene[--i] != NULL)
	{
		if (ft_strncmp(scene[i], "A", 1) == 0 && ft_isspace(scene[i][1]))
			cnt->ambient += 1;
		else if (ft_strncmp(scene[i], "C", 1) == 0 && ft_isspace(scene[i][1]))
			cnt->camera += 1;
		else if (ft_strncmp(scene[i], "L", 1) == 0 && ft_isspace(scene[i][1]))
			cnt->lights += 1;
		else if (is_figure(scene[i]))
			cnt->figures += 1;
		else
		{
			printf("%sLine: %s%s\n", PRINT_PURPLE, PRINT_DEFAULT, scene[i]);
			return (ERR_OBJECT_TYPE);
		}
		if (1 < cnt->ambient || 1 < cnt->camera || 1 < cnt->lights)
		{
			printf("%sLine: %s%s\n", PRINT_PURPLE, PRINT_DEFAULT, scene[i]);
			return (ERR_OBJECT_AMOUNT);
		}
	}
	return (0);
}

static bool	is_figure(char *line)
{
	if (ft_strncmp(line, "sp", 2) == 0 && ft_isspace(line[2]))
		return (true);
	if (ft_strncmp(line, "pl", 2) == 0 && ft_isspace(line[2]))
		return (true);
	if (ft_strncmp(line, "cy", 2) == 0 && ft_isspace(line[2]))
		return (true);
	return (false);
}
