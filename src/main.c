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

// t_vec3	matrix_multiply_vector(t_matrix m, t_vec3 v)
// {
// 	t_vec3	result;

// 	result.x = m.data[0][0] * v.x + m.data[0][1] * v.y + m.data[0][2] * v.z;
// 	result.y = m.data[1][0] * v.x + m.data[1][1] * v.y + m.data[1][2] * v.z;
// 	result.z = m.data[2][0] * v.x + m.data[2][1] * v.y + m.data[2][2] * v.z;
// 	return (result);
// }

// void print_vec3(const char *label, t_vec3 v) {
// 	printf("%s = (%.2f, %.2f, %.2f)\n", label, v.x, v.y, v.z);
// }

// t_ray	transform_ray(t_ray ray, t_matrix matrix)
// {
// 	t_ray	result;

// 	result.orig = matrix_multiply_vec3(matrix, ray.orig);
// 	result.dir = matrix_multiply_vector(matrix, ray.dir);
// 	return (result);
// }


// int main(void) {
// 	// -------------------- TRANSLATION TEST --------------------
// 	t_ray r1;
// 	r1.orig = (t_point){1, 2, 3};
// 	r1.dir = (t_vec3){0, 1, 0};
// 	t_matrix m1 = matrix_translation(3, 4, 5);
// 	t_ray r1_transformed = transform_ray(r1, m1);

// 	printf("Translation Test:\n");
// 	print_vec3("Expected origin", (t_vec3){4, 6, 8});
// 	print_vec3("Actual   origin", r1_transformed.orig);
// 	print_vec3("Expected dir   ", (t_vec3){0, 1, 0});
// 	print_vec3("Actual   dir   ", r1_transformed.dir);
// 	printf("\n");

// 	// -------------------- SCALING TEST --------------------
// 	t_ray r2;
// 	r2.orig = (t_point){1, 2, 3};
// 	r2.dir = (t_vec3){0, 1, 0};
// 	t_matrix m2 = matrix_scaling(2, 3, 4);
// 	t_ray r2_transformed = transform_ray(r2, m2);

// 	printf("Scaling Test:\n");
// 	print_vec3("Expected origin", (t_vec3){2, 6, 12});
// 	print_vec3("Actual   origin", r2_transformed.orig);
// 	print_vec3("Expected dir   ", (t_vec3){0, 3, 0});
// 	print_vec3("Actual   dir   ", r2_transformed.dir);
// 	printf("\n");

// 	return 0;
// }
