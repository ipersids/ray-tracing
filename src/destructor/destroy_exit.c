/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:10:38 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/01 12:53:00 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Frees all allocated resources and exits the program.
 * 
 * @param rt Pointer to the main program structure.
 * @param exit_code Exit code to return from the program.
 */
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
	if (NULL != rt->ts)
		free(rt->ts);
	if (EXIT_SUCCESS != exit_code)
		rt_perror(exit_code);
	exit(exit_code);
}
