/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_destroy_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:10:38 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/09 21:04:43 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

void	rt_destroy_exit(t_info *rt, int exit_code)
{
	if (NULL != rt->objs)
		free(rt->objs);
	if (NULL != rt->lights)
		free(rt->lights);
	if (NULL != rt->win.img)
		mlx_delete_image(rt->win.mlx, rt->win.img);
	if (NULL != rt->win.mlx)
		mlx_terminate(rt->win.mlx);
	if (EXIT_SUCCESS != exit_code)
		rt_perror(exit_code);
	exit(exit_code);
}
