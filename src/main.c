#include "minirt.h"

static void	run_unit_tests(void)
{
	printf(PRINT_GREEN"RUNNING UNIT TESTS:"PRINT_DEFAULT);
	test_matrix_math();
	test_matrix_transformation();
	printf("\n\n");
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
	exit_code = rt_init_canvas(&rt);
	if (0 != exit_code)
		rt_destroy_exit(&rt, exit_code);
	rt_destroy_exit(&rt, EXIT_SUCCESS);
	return (exit_code);
}
