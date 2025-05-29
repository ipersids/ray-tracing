#ifndef MINIRT_MATRIX_H
# define MINIRT_MATRIX_H

/* -------------------------- Matrix constructors  ------------------------- */

/// @file src/calculations/matrices/create_base_matrix.c

t_matrix	matrix_empty(void);
t_matrix	matrix_identity(void);
bool		matrix_equality(t_matrix a, t_matrix b);
t_matrix	matrix_transpose(t_matrix self);

/// @file src/calculations/matrices/create_base_transform.c

t_matrix	matrix_translation(float x, float y, float z);
t_matrix	matrix_scaling(float x, float y, float z);
t_matrix	matrix_rotation_x(float radians);
t_matrix	matrix_rotation_y(float radians);
t_matrix	matrix_rotation_z(float radians);

/// @file src/calculations/matrices/create_chaining_transform.c

t_matrix	matrix_shearing(float proportions[6]);

/* ------------------------------- Operations  ------------------------------ */

/// @file src/calculations/matrices/operations.c

t_matrix	matrix_multiply(t_matrix a, t_matrix b);
// t_vec3		matrix_multiply_vec3(t_matrix m, t_vec3 v);
t_vec3		matrix_multiply_point(t_matrix m, t_vec3 p);
t_vec3		matrix_multiply_vector(t_matrix m, t_vec3 v);

/// @file src/calculations/matrices/extract_submatrix.c

typedef struct s_submatrix_var
{
	t_matrix	res;
	size_t		row;
	size_t		col;
	size_t		src_row;
	size_t		src_col;
}				t_subm_var;

t_matrix	submatrix(t_matrix self, size_t rm_row, size_t rm_col);

/// @file /// @file src/calculations/matrices/inverse.c

float		matrix_determinant(t_matrix m);
float		matrix_cofactor(t_matrix m, size_t row, size_t col);
float		matrix_minor(t_matrix m, size_t row, size_t col);
bool		matrix_try_inverse(t_matrix m, t_matrix *res);
t_matrix	inverse(t_matrix matrix); // THIS MIGHT BE NOT NEEDED

/* -------------------------- Math helper functions ------------------------- */

/// @file src/calculations/radians.c

float		radians(float degrees);

#endif // MINIRT_MATRIX_H
