/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_destroy_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:10:38 by ipersids          #+#    #+#             */
/*   Updated: 2025/04/29 18:56:03 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_destroy_exit(t_info *rt, int exit_code)
{
	if (NULL != rt->objs)
		free(rt->objs);
	if (NULL != rt->lights)
		free(rt->lights);
	if (EXIT_SUCCESS != exit_code)
		rt_perror(exit_code);
	exit(exit_code);
}
