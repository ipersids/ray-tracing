#ifndef MINIRT_MATRIX_H
# define MINIRT_MATRIX_H

# ifndef MINIRT_DATA_H
typedef unsigned long size_t;
# endif

# include <math.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define M_SIZE 4

typedef struct s_matrix
{
	float	data[M_SIZE][M_SIZE];
	size_t	dimension;
}			t_matrix;

typedef enum e_proportions
{
	XY,
	XZ,
	YX,
	YZ,
	ZX,
	ZY
}	t_proportions;

/* -------------------------- Matrix constructors  ------------------------- */

/// @file src/calculations/matrices/create_base_matrix.c

t_matrix	empty(void);
t_matrix	identity(void);

/// @file src/calculations/matrices/create_base_transform.c

t_matrix	translation(float x, float y, float z);
t_matrix	scaling(float x, float y, float z);
t_matrix	rotation_x(float radians);
t_matrix	rotation_y(float radians);
t_matrix	rotation_z(float radians);

/// @file src/calculations/matrices/create_chaining_transform.c

t_matrix	shearing(float proportions[6]);

/* -------------------------- Math helper functions ------------------------- */

float		radians(float degrees);

#endif // MINIRT_MATRIX_H