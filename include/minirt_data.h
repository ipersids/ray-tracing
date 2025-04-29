/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_data.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:35:35 by ipersids          #+#    #+#             */
/*   Updated: 2025/04/29 18:55:28 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_DATA_H
# define MINIRT_DATA_H

# define EXTENSION ".rt"

/**
 * @brief Colors palette
 */
# define PRINT_RED "\033[0;31m"
# define PRINT_GREEN "\033[0;32m"
# define PRINT_PURPLE "\033[0;35m"
# define PRINT_DEFAULT "\033[0m"

# ifndef IS_BONUS
#  define IS_BONUS false
# endif

/* ------------------- File validation and errors handling  ----------------- */

/**
 * @brief Error codes
 * 
 * - ERR_SYSTEM: callback strerror(errno);
 * - ERR_MLX42: callback mlx_strerror(mlx_errno);
 * 
 * Internal program errors:
 * - ERR_AGRC: The program received the wrong number of arguments.
 * - ERR_EXTENSION: The file has an incorrect extension.
 * 
 * - ERR_MAX - limiter for array of error messages.
 */
typedef enum s_error
{
	ERR_SYSTEM = 98,
	ERR_MLX42,
	ERR_ARGC,
	ERR_EXTENSION,
	ERR_OVERFLOW,
	ERR_OBJECT_TYPE,
	ERR_OBJECT_AMOUNT,
	ERR_OBJECT_CONFIG,
	ERR_OBJECT_CONFIG_LIMITS,
	ERR_MAX
}	t_error;

# define ERR_MODULO ERR_ARGC
# define CAPACITY 10
# define NULL_TERMINATED_ARR -1

# define R 0
# define G 1
# define B 2

# define X 0
# define Y 1
# define Z 2

/* ---------------------------- Scene structures  -------------------------- */

typedef enum e_type
{
	ELEMENT_AMBIENT,
	ELEMENT_CAMERA,
	ELEMENT_LIGHT,
	ELEMENT_SPHERE,
	ELEMENT_PLANE,
	ELEMENT_CYLINDER,
	ELEMENT_UKNOWN
}	t_type;

# define LIMIT_COORD 10000.0f

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}			t_point;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}		t_color;

# define DEFAULT_AMBIENT_RATIO 0.2
# define DEFAULT_AMBIENT_COLOR_R 255
# define DEFAULT_AMBIENT_COLOR_G 255
# define DEFAULT_AMBIENT_COLOR_B 255

typedef struct s_ambient_light
{
	float	ratio;				// amb. lighting ratio in range [0.0,1.0]: 0.2
	t_color	color;				// R,G,B colors in range [0-255]: 255,255,255
}			t_ambient_light;

# define DEFAULT_CAMERA_POSITION_X -50.0
# define DEFAULT_CAMERA_POSITION_Y 0.0
# define DEFAULT_CAMERA_POSITION_Z 20.0
# define DEFAULT_CAMERA_DIRECTION_X 0.0
# define DEFAULT_CAMERA_DIRECTION_Y 0.0
# define DEFAULT_CAMERA_DIRECTION_Z 1.0
# define DEFAULT_CAMERA_FOV 70

typedef struct s_camera
{
	t_point	pos;				// x,y,z of the camera position: -50.0,0,20
	t_point	dir;				// 3d norm. orientation vector: 0.0,0.0,1.0
	int		fov;				// Horizontal field of view, degrees [0,180]: 70
}			t_camera;

# define DEFAULT_LIGHT_POSITION_X -40.0
# define DEFAULT_LIGHT_POSITION_Y 50.0
# define DEFAULT_LIGHT_POSITION_Z 0.0
# define DEFAULT_LIGHT_BRIGHTNESS 0.6
// # define DEFAULT_LIGHT_COLOR {10, 0, 255}

typedef struct s_light
{
	t_point	pos;				// x,y,z of the light point: -40.0,50.0,0.0
	float	bright;				// the light brightness ratio [0.0,1.0]: 0.6
	t_color	color;				// (unused in mandatory part)
}			t_light;

typedef struct s_sphere
{
	t_point	pos;				// x,y,z of sphere center: 0.0,0.0,20.6
	float	diam;				// the sphere diameter: 12.6
	t_color	color;				// R,G,B colors in range [0-255]: 10, 0, 255
}			t_sphere;

typedef struct s_plane
{
	t_point	pos;				// x,y,z of a point on plane: 0.0,0.0,-10.0
	t_point	dir;				// 3d norm. orientation vector: 0.0,1.0,0.0
	t_color	color;				// R,G,B colors in range [0-255]: 0,0,225
}			t_plane;

typedef struct s_cylinder
{
	t_point	pos;				// center point of cy. base: 50.0,0.0,20.6
	t_point	dir;				// 3d norm. vector of cy.axis: 0.0,0.0,1.0
	float	diam;				// the cylinder diameter: 14.2
	float	height;				// the cylinder height: 21.42
	t_color	color;				// R,G,B colors in range [0,255]: 10, 0, 255
}			t_cylinder;

typedef struct s_object
{
	t_type			id;
	union
	{
		t_sphere	sp;
		t_plane		pl;
		t_cylinder	cy;
	};
}					t_object;

/* -------------------------- Main minirt structure  ----------------------- */

typedef struct s_info
{
	t_ambient_light	ambient;
	t_camera		camera;
	t_light			*lights;
	t_object		*objs;
	size_t			n_objs;
	size_t			n_lights;
}	t_info;

/* ------------------------- Parser helper structures ----------------------- */

typedef struct s_counter
{
	int	figures;
	int	lights;
	int	camera;
	int	ambient;
}		t_counter;

#endif // MINIRT_DATA_H