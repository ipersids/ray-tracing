#ifndef MINIRT_MATH_H
# define MINIRT_MATH_H

# include "minirt_data.h"

/// @file src/calculations/vectors/
/* -------------------------- Vector calculations -------------------------- */

t_vec3		addition(t_vec3 vec_a, t_vec3 vec_b);
t_vec3		subtraction(t_vec3 vec_a, t_vec3 vec_b);
t_vec3		negation(t_vec3 vec);
t_vec3		multiplication(t_vec3 vec, float multiplier);
t_vec3		division(t_vec3 vec, float divider);
t_vec3		normalize(t_vec3 vec);
t_vec3		cross_product(t_vec3 a, t_vec3 b);
float		magnitude(t_vec3 vec);
float		dot_product(t_vec3 a, t_vec3 b);

/// @file src/calculations/matrices/
/* -------------------------- Matrix constructors -------------------------- */

t_matrix	matrix_empty(void);
t_matrix	matrix_identity(void);
bool		matrix_equality(t_matrix a, t_matrix b);
t_matrix	matrix_transpose(t_matrix self);
t_matrix	matrix_translation(float x, float y, float z);
t_matrix	matrix_scaling(float x, float y, float z);
t_matrix	matrix_rotation_x(float radians);
t_matrix	matrix_rotation_y(float radians);
t_matrix	matrix_rotation_z(float radians);
t_matrix	matrix_rotation(t_vec3 from_norm, t_vec3 to_norm);
t_matrix	matrix_shearing(float proportions[6]);

/// @file src/calculations/matrices/
/* -------------------------- Matrix Operations ---------------------------- */

t_matrix	matrix_multiply(t_matrix a, t_matrix b);
t_vec3		matrix_multiply_point(t_matrix m, t_vec3 p);
t_vec3		matrix_multiply_vector(t_matrix m, t_vec3 v);
t_matrix	submatrix(t_matrix self, size_t rm_row, size_t rm_col);
float		matrix_determinant(t_matrix m);
float		matrix_cofactor(t_matrix m, size_t row, size_t col);
float		matrix_minor(t_matrix m, size_t row, size_t col);
bool		matrix_try_inverse(t_matrix m, t_matrix *res);

/// @file src/calculations/colors.c
/* --------------------------- Color Operations ----------------------------- */

t_color		multiply_colors(t_color a, t_color b);
t_color		multiply_color_scalar(t_color a, float scalar);
uint32_t	rt_convert_to_rgba(const t_color *color);

/// @file src/calculations/
/* -------------------------- Math helper functions ------------------------- */

float		radians(float degrees);
bool		equal(float a, float b);

#endif // MINIRT_MATH_H
