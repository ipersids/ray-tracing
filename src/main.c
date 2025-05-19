/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:55:51 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/19 16:17:21 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// int	main(int argc, char **argv)
// {
// 	int		exit_code;
// 	t_info	rt;

// 	rt_init_info(&rt);
// 	exit_code = rt_validate_input(argc, argv, &rt);
// 	if (0 != exit_code)
// 		rt_destroy_exit(&rt, exit_code);
// 	ft_printf("%s\n", argv[1]);
// 	debug_print_info(&rt);
// 	exit_code = rt_init_canvas(&rt);
// 	if (0 != exit_code)
// 		rt_destroy_exit(&rt, exit_code);
// 	rt_destroy_exit(&rt, EXIT_SUCCESS);
// 	return (exit_code);
// }

static void print_matrix(t_matrix m, char* msg)
{
	printf("%s\n", msg);
	for(int i = 0; i < 4; i++) {
		printf("[%.2f, %.2f, %.2f, %.2f]\n",
			m.data[i][0], m.data[i][1],
			m.data[i][2], m.data[i][3]
		);
	}
	printf("\n\n");
}

int main(void) {
	t_matrix new_empty = empty();
	t_matrix new_ident = identity();
	t_matrix new_translation = translation(12.0, 13.0, 14.0);
	t_matrix new_scaling = scaling(12.0, 13.0, 14.0);
	t_matrix new_rotation_x = rotation_x(90.0);
	t_matrix new_rotation_y = rotation_y(90.0);
	t_matrix new_rotation_z = rotation_z(90.0);
	float arr[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
	t_matrix new_shearing = shearing(arr);

	print_matrix(new_empty, "new_empty:");
	print_matrix(new_ident, "new_ident:");
	print_matrix(new_translation, "new_translation:");
	print_matrix(new_scaling, "new_scaling:");
	print_matrix(new_rotation_x, "new_rotation_x:");
	print_matrix(new_rotation_y, "new_rotation_y:");
	print_matrix(new_rotation_z, "new_rotation_z:");
	print_matrix(new_shearing, "new_shearing:");
}
