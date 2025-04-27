/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_validate_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 00:51:02 by ipersids          #+#    #+#             */
/*   Updated: 2025/04/20 01:45:12 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_validate_args(int argc, char **argv)
{
	char	*slash;
	char	*name;
	int		name_len;

	if (2 != argc)
	{
		rt_perror(ERR_ARGC);
		return (ERR_ARGC);
	}
	name = argv[1];
	slash = ft_strrchr(name, '/');
	if (NULL != slash)
		name = slash + 1;
	name_len = (int)ft_strlen(name) - (int)ft_strlen(EXTENTION);
	if (0 >= name_len || ft_strcmp(&name[name_len], EXTENTION))
	{
		rt_perror(ERR_EXTENSION);
		return (ERR_EXTENSION);
	}
	return (EXIT_SUCCESS);
}
