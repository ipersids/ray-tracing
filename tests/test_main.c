#include "minirt_tests.h"

static void	run_unit_tests(void)
{
	printf(PRINT_GREEN"RUNNING UNIT TESTS:"PRINT_DEFAULT);
	test_parser();
	test_matrix_math();
	test_matrix_transformation();
	test_camera();
	test_cone();
	printf("\n\n");
}

int	main(void)
{
	run_unit_tests();
	return (0);
}