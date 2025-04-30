/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:55:51 by ipersids          #+#    #+#             */
/*   Updated: 2025/04/30 14:11:22 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	debug_print_info(t_info *rt);

int	main(int argc, char **argv)
{
	int		exit_code;
	t_info	rt;

	rt_init_info(&rt);
	exit_code = rt_validate_input(argc, argv, &rt);
	if (0 != exit_code)
		rt_destroy_exit(&rt, exit_code);
	ft_printf("%s\n", argv[1]);
	debug_print_info(&rt);
	rt_destroy_exit(&rt, EXIT_SUCCESS);
	return (exit_code);
}

static void	debug_print_info(t_info *rt)
{
	printf(PRINT_GREEN"AMBIENT:\n"PRINT_DEFAULT);
	printf("\t- ratio: %f\n", rt->ambient.ratio);
	printf("\t- color: %f, %f, %f\n", rt->ambient.color.x, rt->ambient.color.y, rt->ambient.color.z);
	printf(PRINT_GREEN"\nCAMERA:\n"PRINT_DEFAULT);
	printf("\t- position: %.2f, %.2f, %.2f\n", rt->camera.pos.x, rt->camera.pos.y, rt->camera.pos.z);
	printf("\t- direction: %.2f, %.2f, %.2f\n", rt->camera.dir.x, rt->camera.dir.y, rt->camera.dir.z);
	printf("\t- FOV: %f\n", rt->camera.fov);
	printf(PRINT_GREEN"\nLIGHTS:\n"PRINT_DEFAULT);
	for (size_t i = 0; i < rt->n_lights; i++) {
		printf("Light [%zu/%zu]:\n", i + 1, rt->n_lights);
		printf("\t- position: %.2f, %.2f, %.2f\n", rt->lights[i].pos.x, rt->lights[i].pos.y, rt->lights[i].pos.z);
		printf("\t- brightness: %.2f\n", rt->lights[i].bright);
		printf("\t- color: %f, %f, %f\n", rt->lights[i].color.x, rt->lights[i].color.y, rt->lights[i].color.z);
	}
}
