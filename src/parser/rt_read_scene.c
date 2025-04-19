/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_read_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:05:03 by ipersids          #+#    #+#             */
/*   Updated: 2025/04/20 13:47:23 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static char	**realloc_matrix(char **arr, int i, int *size, int *exit_code);
static bool	is_empty_line(char *nl, char *line);

/* --------------------------- Public functions ---------------------------- */

int	rt_read_scene(int fd, char ***content)
{
	static int	row = 0;
	static int	exit_code = 0;
	int			capacity;
	char		*nl;

	capacity = CAPACITY;
	(*content) = (char **) malloc(capacity * sizeof(char *));
	if (!(*content))
		return (ERR_SYSTEM);
	(*content)[row] = get_next_line(fd, FALSE);
	while ((*content)[row])
	{
		nl = ft_strchr((*content)[row], '\n');
		if (!is_empty_line(nl, (*content)[row]))
			++row;
		if (row > capacity)
		{
			(*content) = realloc_matrix((*content), row, &capacity, &exit_code);
			if (!(*content))
				return (exit_code);
		}
		(*content)[row] = get_next_line(fd, FALSE);
	}
	return (EXIT_SUCCESS);
}

/* ------------------- Private function implementation --------------------- */

static char	**realloc_matrix(char **arr, int i, int *size, int *exit_code)
{
	char	**res;
	int		j;

	if (*size > *size * 2)
	{
		rt_free_arr((void **)arr, i);
		*exit_code = ERR_OVERFLOW;
		return (NULL);
	}
	*size = *size * 2;
	res = (char **) malloc(*size * sizeof(char *));
	if (!res)
	{
		rt_free_arr((void **)arr, i);
		*exit_code = ERR_SYSTEM;
		return (NULL);
	}
	j = 0;
	while (j < i)
	{
		res[j] = arr[j];
		j++;
	}
	free(arr);
	return (res);
}

static bool	is_empty_line(char *nl, char *line)
{
	size_t	line_len;
	size_t	i;

	if (nl)
		*nl = '\0';
	line_len = ft_strlen(line);
	if (0 == line_len)
	{
		free(line);
		return (true);
	}
	i = 0;
	while (i < line_len)
	{
		if (!ft_isspace(line[i]))
			break ;
		i++;
	}
	if ('\0' == line[i])
	{
		free(line);
		return (true);
	}
	return (false);
}
