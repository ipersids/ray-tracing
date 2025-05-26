#include "minirt.h"

static void	run_unit_tests(void)
{
	printf(PRINT_GREEN"RUNNING UNIT TESTS:"PRINT_DEFAULT);
	test_matrix_math();
	test_matrix_transformation();
	printf("\n\n");
}

// int	main(int argc, char **argv)
// {
// 	int		exit_code;
// 	t_info	rt;

// 	run_unit_tests(); /// @note delete
// 	rt_init_info(&rt);
// 	exit_code = rt_validate_input(argc, argv, &rt);
// 	if (0 != exit_code)
// 		rt_destroy_exit(&rt, exit_code);
// 	ft_printf("File: %s\n", argv[1]); /// @note delete
// 	debug_print_info(&rt); /// @note delete
// 	exit_code = rt_init_canvas(&rt);
// 	if (0 != exit_code)
// 		rt_destroy_exit(&rt, exit_code);
// 	rt_destroy_exit(&rt, EXIT_SUCCESS);
// 	return (exit_code);
// }

t_vec3	reflect(t_vec3 in, t_vec3 normal)
{
	t_vec3	result;
	t_vec3	scaled_norm;

	scaled_norm = multiplication(normal, 2 * dot_product(in, normal));
	result = subtraction(in, scaled_norm);
	return (result);
}

void	print_vector(char *msg, t_vec3 vec)
{
	printf("%s x = %.2f y = %.2f z = %.2f\n", msg, vec.x, vec.y, vec.z);
}

int	main(int argc, char **argv)
{
	int		exit_code;
	t_info	rt;

	run_unit_tests(); /// @note delete
	rt_init_info(&rt);
	exit_code = rt_validate_input(argc, argv, &rt);
	if (0 != exit_code)
		rt_destroy_exit(&rt, exit_code);
	ft_printf("File: %s\n", argv[1]); /// @note delete
	debug_print_info(&rt); /// @note delete
	t_matrix	translation = matrix_translation(0, 1, 0);
	rt.objs[0].sp.transform = translation;
	t_vec3 n = normal_at(rt.objs[0].sp, (t_point){0, 1.70711, -0.70711});
	print_vector("Normal at vector: ", n);
	t_vec3	reflection = reflect((t_vec3){0, -1, 0}, (t_vec3){sqrt(2) / 2, sqrt(2) / 2, 0});
	print_vector("Reflect ", reflection);
	return (0);
}
