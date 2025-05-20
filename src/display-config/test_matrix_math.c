/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_matrix_math.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:11:33 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/20 14:29:58 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	test_matrix_math(void)
{
	printf(PRINT_PURPLE"\n\nTEST MATRIX MATH: \n"PRINT_DEFAULT);

	printf("TEST EQUALITY: ");
	t_matrix m1 = {{{0.0, 1.0}, {2.0, 3.0}}, 2};
	t_matrix m2 = {{{0.0, 1.0}, {2.0, 3.0}}, 2};
	t_matrix m3 = {{{0.0, 1.5}, {2.0, 3.0}}, 2};
	assert(matrix_equality(m1, m2) == true);
	assert(matrix_equality(m1, m3) == false);
	printf(PRINT_GREEN"success\n"PRINT_DEFAULT);

	printf("TEST MULTUPLICATION: \n");
	printf("\t- matrix * matrix: ");
	t_matrix m4 = {
            {{1.0, 2.0, 3.0, 4.0},
            {5.0, 6.0, 7.0, 8.0},
            {9.0, 8.0, 7.0, 6.0},
            {5.0, 4.0, 3.0, 2.0}},
        4};

    t_matrix m5 = {
            {{-2.0, 1.0, 2.0, 3.0},
            {3.0, 2.0, 1.0, -1.0},
            {4.0, 3.0, 6.0, 5.0},
            {1.0, 2.0, 7.0, 8.0}},
        4};

    t_matrix m6 = matrix_multiply(m4, m5);
	assert(equal(m6.data[0][0], 20.0) == true);
    assert(equal(m6.data[0][1], 22.0) == true);
    assert(equal(m6.data[0][2], 50.0) == true);
    assert(equal(m6.data[0][3], 48.0) == true);
    assert(equal(m6.data[1][0], 44.0) == true);
    assert(equal(m6.data[1][1], 54.0) == true);
    assert(equal(m6.data[1][2], 114.0) == true);
    assert(equal(m6.data[1][3], 108.0) == true);
    assert(equal(m6.data[2][0], 40.0) == true);
    assert(equal(m6.data[2][1], 58.0) == true);
    assert(equal(m6.data[2][2], 110.0) == true);
    assert(equal(m6.data[2][3], 102.0) == true);
    assert(equal(m6.data[3][0], 16.0) == true);
    assert(equal(m6.data[3][1], 26.0) == true);
    assert(equal(m6.data[3][2], 46.0) == true);
    assert(equal(m6.data[3][3], 42.0) == true);
	printf(PRINT_GREEN"success\n"PRINT_DEFAULT);
	printf("\t- matrix * vec3: ");
	t_matrix m7 = {
			{{1.0, 2.0, 3.0, 4.0},
			{2.0, 4.0, 4.0, 2.0},
			{8.0, 6.0, 4.0, 1.0},
			{0.0, 0.0, 0.0, 1.0}},
		4};
	t_vec3 v1 = {1.0, 2.0, 3.0};
	t_vec3 v2 = matrix_multiply_vec3(m7, v1);
	assert(equal(v2.x, 18.0) == true);
    assert(equal(v2.y, 24.0) == true);
    assert(equal(v2.z, 33.0) == true);
    printf(PRINT_GREEN"success\n"PRINT_DEFAULT);

	printf("TEST TRANSPOSE: ");
	t_matrix m8 = {
			{{0.0, 9.0, 3.0, 0.0},
			{9.0, 8.0, 0.0, 8.0},
			{1.0, 8.0, 5.0, 3.0},
			{0.0, 0.0, 5.0, 8.0}},
		4};
	t_matrix m9 = {
			{{0.0, 9.0, 1.0, 0.0},
			{9.0, 8.0, 8.0, 0.0},
			{3.0, 0.0, 5.0, 5.0},
			{0.0, 8.0, 3.0, 8.0}},
		4};
	t_matrix m10 = matrix_transpose(m8);
	t_matrix m11 = matrix_identity();
	t_matrix m12 = matrix_transpose(m11);
	assert(matrix_equality(m8, m9) == false);
	assert(matrix_equality(m9, m10) == true);
	assert(matrix_equality(m11, m12) == true);
	printf(PRINT_GREEN"success\n"PRINT_DEFAULT);

	printf("TEST SUBMATRIX: ");
	t_matrix m13 = {
			{{1., 5.0, 0.0},
			{-3.0, 2.0, 7.0},
			{0.0, 6.0, -3.0}},
		3};
	t_matrix m14 = submatrix(m13, 0, 2);
	t_matrix m15 = {
			{{-3.0, 2.0},
			{0.0, 6.0}},
		2};
	assert(matrix_equality(m13, m15) == false);
	assert(matrix_equality(m14, m15) == true);
	assert(m14.dimension == m15.dimension && m14.dimension == 2);
	printf(PRINT_GREEN"success\n"PRINT_DEFAULT);

	printf("TEST DETERMINANT: ");
	t_matrix m16 = {
			{{1.0, 5.0},
			{-3.0, 2.0}},
		2};
	float det1 = matrix_determinant(m16);
	assert(equal(det1, 17.0) == true);
	t_matrix m17 = {
			{{1.0, 2.0, 6.0},
			{-5.0, 8.0, -4.0},
			{2.0, 6.0, 4.0}},
		3};
	float det2 = matrix_determinant(m17);
	assert(equal(det2, -196.0) == true);
	t_matrix m18 = {
			{{-2.0, -8.0, 3.0, 5.0},
			{-3.0, 1.0, 7.0, 3.0},
			{1.0, 2.0, -9.0, 6.0},
			{-6.0, 7.0, 7.0, -9.0}},
		4};
	float det3 = matrix_determinant(m18);
	assert(equal(det3, -4071.0) == true);
	t_matrix m19 = {
			{{-4.0, 2.0, -2.0, -3.0},
			{9.0, 6.0, 2.0, 6.0},
			{0.0, -5.0, 1.0, -5.0},
			{0.0, 0.0, 0.0, 0.0}},
		4};
	float det4 = matrix_determinant(m19);
	assert(equal(det4, 0.0) == true);
	printf(PRINT_GREEN"success\n"PRINT_DEFAULT);

	printf("TEST MINOR: ");
	t_matrix m24 = {
			{{3.0, 5.0, 0.0},
			{2.0, -1.0, -7.0},
			{6.0, -1.0, 5.0}},
		3};
	float min1 = matrix_minor(m24, 1, 0);
	assert(equal(min1, 25.0) == true);
	printf(PRINT_GREEN"success\n"PRINT_DEFAULT);

	printf("TEST COFACTOR: ");
	float min2 = matrix_minor(m24, 0, 0);
	float cof2 = matrix_cofactor(m24, 0, 0);
	assert(equal(min2, cof2) == true);
	assert(equal(cof2, -12.0) == true);
	float min3 = matrix_minor(m24, 1, 0);
	float cof3 = matrix_cofactor(m24, 1, 0);
	assert(equal(min3, cof3) == false);
	assert(equal(cof3, -25.0) == true);
	printf(PRINT_GREEN"success\n"PRINT_DEFAULT);

	printf("TEST INVERSE: ");
	t_matrix m20 = matrix_empty();
	t_matrix m21 = matrix_empty();
	bool res1 = matrix_try_inverse(m19, &m20);
	assert(res1 == false && matrix_equality(m20, m21));
	t_matrix m22 = {
			{{8.0, -5.0, 9.0, 2.0},
			{7.0, 5.0, 6.0, 1.0},
			{-6.0, 0.0, 9.0, 6.0},
			{-3.0, 0.0, -9.0, -4.0}},
		4};
	t_matrix m23 = {
			{{-0.15385, -0.15385, -0.28205, -0.53846},
			{-0.07692, 0.12308, 0.02564, 0.03077},
			{0.35897, 0.35897, 0.43590, 0.92308},
			{-0.69231, -0.69231, -0.76923, -1.92308}},
		4};
	bool res2 = matrix_try_inverse(m22, &m20);
	assert(res2 == true && matrix_equality(m20, m23));
	t_matrix m25 = {
			{{6.0, 4.0, 4.0, 4.0},
			{5.0, 5.0, 7.0, 6.0},
			{4.0, -9.0, 3.0, -7.0},
			{9.0, 1.0, 7.0, -6.0}},
		4};
	t_matrix m26 = matrix_multiply(m22, m25);
	t_matrix inverse_m25 = matrix_empty();
	bool res3 = matrix_try_inverse(m25, &inverse_m25);
	assert(res3 == true);
	t_matrix restored_m22 = matrix_multiply(m26, inverse_m25);
	assert(matrix_equality(m22, restored_m22) == true);
	printf(PRINT_GREEN"success\n"PRINT_DEFAULT);
}