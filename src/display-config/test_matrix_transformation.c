/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_matrix_transformation.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:21:14 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/29 13:13:51 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	test_matrix_transformation(void)
{
	printf(PRINT_PURPLE"\n\nTEST MATRIX TRANSFORMATIONS: \n"PRINT_DEFAULT);
	
	printf("TEST multiplying point by a translation matrix: ");
	t_matrix m1 = matrix_translation(5.0, -3.0, 2.0);
	t_point v1 = {-3.0, 4.0, 5.0};
	t_point res1 = matrix_multiply_point(m1, v1);
	assert(equal(res1.x, 2.0) && equal(res1.y, 1.0) && equal(res1.z, 7.0));
	printf(PRINT_GREEN"success\n"PRINT_DEFAULT);

	printf("TEST multiplying point by the inverse of a translation matrix: ");
	t_matrix inverse_m1 = matrix_empty();
	assert(matrix_try_inverse(m1, &inverse_m1));
	t_point res2 = matrix_multiply_point(inverse_m1, v1);
	assert(equal(res2.x, -8.0) && equal(res2.y, 7.0) && equal(res2.z, 3.0));
	printf(PRINT_GREEN"success\n"PRINT_DEFAULT);

	printf("TEST scaling matrix applied to a point or vector: ");
	m1 = matrix_scaling(2.0, 3.0, 4.0);
	t_point v2 = {-4.0, 6.0, 8.0};
	res2 = matrix_multiply_point(m1, v2);
	assert(equal(res2.x, -8.0) && equal(res2.y, 18.0) && equal(res2.z, 32.0));
	inverse_m1 = matrix_empty();
	assert(matrix_try_inverse(m1, &inverse_m1));
	res2 = matrix_multiply_point(inverse_m1, v2);
	assert(equal(res2.x, -2.0) && equal(res2.y, 2.0) && equal(res2.z, 2.0));
	m1 = matrix_scaling(-1.0, 1.0, 1.0);
	t_vec3 v3 = {2.0, 3.0, 4.0};
	res2 = matrix_multiply_vector(m1, v3);
	assert(equal(res2.x, -2.0) && equal(res2.y, 3.0) && equal(res2.z, 4.0));
	printf(PRINT_GREEN"success\n"PRINT_DEFAULT);

	printf("TEST rotating a point around the x axis: ");
	t_point v4 = {0.0, 1.0, 0.0};
	t_matrix half_quarter = matrix_rotation_x(M_PI / 4.0);
	t_matrix full_quarter = matrix_rotation_x(M_PI / 2.0);
	t_point res3 = matrix_multiply_point(half_quarter, v4);
	assert(equal(res3.x, 0.0) && equal(res3.y, sqrt(2) / 2.0) && equal(res3.z, sqrt(2) / 2.0));
	res3 = matrix_multiply_point(full_quarter, v4);
	assert(equal(res3.x, 0.0) && equal(res3.y, 0.0) && equal(res3.z, 1.0));
	t_matrix inverse_half_quarter = matrix_empty();
	assert(matrix_try_inverse(half_quarter, &inverse_half_quarter));
	res3 = matrix_multiply_point(inverse_half_quarter, v4);
	assert(equal(res3.x, 0.0) && equal(res3.y, sqrt(2) / 2.0) && equal(res3.z, -(sqrt(2) / 2.0)));
	printf(PRINT_GREEN"success\n"PRINT_DEFAULT);

	printf("TEST rotating a point around the y axis: ");
	t_point v5 = {0.0, 0.0, 1.0};
	half_quarter = matrix_rotation_y(M_PI / 4.0);
	full_quarter = matrix_rotation_y(M_PI / 2.0);
	res3 = matrix_multiply_point(half_quarter, v5);
	assert(equal(res3.x, sqrt(2) / 2.0) && equal(res3.y, 0.0) && equal(res3.z, sqrt(2) / 2.0));
	res3 = matrix_multiply_point(full_quarter, v5);
	assert(equal(res3.x, 1.0) && equal(res3.y, 0.0) && equal(res3.z, 0.0));
	printf(PRINT_GREEN"success\n"PRINT_DEFAULT);

	printf("TEST rotating a point around the z axis: ");
	t_point v6 = {0.0, 1.0, 0.0};
	half_quarter = matrix_rotation_z(M_PI / 4.0);
	full_quarter = matrix_rotation_z(M_PI / 2.0);
	res3 = matrix_multiply_point(half_quarter, v6);
	assert(equal(res3.x, -(sqrt(2) / 2.0)) && equal(res3.y, sqrt(2) / 2.0) && equal(res3.z, 0.0));
	res3 = matrix_multiply_point(full_quarter, v6);
	assert(equal(res3.x, -1.0) && equal(res3.y, 0.0) && equal(res3.z, 0.0));
	printf(PRINT_GREEN"success\n"PRINT_DEFAULT);

	printf("TEST shearing transformations: ");
	float arr[6] = {1.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	m1 = matrix_shearing(arr);
	t_point v7 = {2.0, 3.0, 4.0};
	t_point res4 = matrix_multiply_vector(m1, v7);
	assert(equal(res4.x, 5.0) && equal(res4.y, 3.0) && equal(res4.z, 4.0));
	arr[0] = 0.0;
	arr[1] = 1.0;
	m1 = matrix_shearing(arr);
	res4 = matrix_multiply_vector(m1, v7);
	assert(equal(res4.x, 6.0) && equal(res4.y, 3.0) && equal(res4.z, 4.0));
	arr[1] = 0.0;
	arr[2] = 1.0;
	m1 = matrix_shearing(arr);
	res4 = matrix_multiply_vector(m1, v7);
	assert(equal(res4.x, 2.0) && equal(res4.y, 5.0) && equal(res4.z, 4.0));
	arr[2] = 0.0;
	arr[3] = 1.0;
	m1 = matrix_shearing(arr);
	res4 = matrix_multiply_vector(m1, v7);
	assert(equal(res4.x, 2.0) && equal(res4.y, 7.0) && equal(res4.z, 4.0));
	arr[3] = 0.0;
	arr[4] = 1.0;
	m1 = matrix_shearing(arr);
	res4 = matrix_multiply_vector(m1, v7);
	assert(equal(res4.x, 2.0) && equal(res4.y, 3.0) && equal(res4.z, 6.0));
	arr[4] = 0.0;
	arr[5] = 1.0;
	m1 = matrix_shearing(arr);
	res4 = matrix_multiply_vector(m1, v7);
	assert(equal(res4.x, 2.0) && equal(res4.y, 3.0) && equal(res4.z, 7.0));
	printf(PRINT_GREEN"success\n"PRINT_DEFAULT);

	printf("TEST chaining transformations: ");
	t_point p = {1.0, 0.0, 1.0};
	t_matrix rot_x = matrix_rotation_x(M_PI / 2.0);
	t_matrix scal = matrix_scaling(5.0, 5.0, 5.0);
	t_matrix transl = matrix_translation(10.0, 5.0, 7.0);
	t_point rot_p = matrix_multiply_point(rot_x, p);
	assert(equal(rot_p.x, 1.0) && equal(rot_p.y, -1.0) && equal(rot_p.z, 0.0));
	t_point scal_p = matrix_multiply_point(scal, rot_p);
	assert(equal(scal_p.x, 5.0) && equal(scal_p.y, -5.0) && equal(scal_p.z, 0.0));
	t_point transl_p = matrix_multiply_point(transl, scal_p);
	assert(equal(transl_p.x, 15.0) && equal(transl_p.y, 0.0) && equal(transl_p.z, 7.0));
	t_matrix tramsf = matrix_multiply(matrix_multiply(transl, scal), rot_x);
	t_point res5 = matrix_multiply_point(tramsf, p);
	assert(equal(res5.x, 15.0) && equal(res5.y, 0.0) && equal(res5.z, 7.0));
	printf(PRINT_GREEN"success\n"PRINT_DEFAULT);
}
