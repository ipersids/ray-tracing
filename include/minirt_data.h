/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_data.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:35:35 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/09 23:01:55 by ipersids         ###   ########.fr       */
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
# define LIMIT_S 10000.0f

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}			t_vec3;

typedef t_vec3	t_point;

typedef t_vec3	t_color;

# define DEFAULT_AMBIENT_RATIO 0.2
# define DEFAULT_AMBIENT_COLOR_R 255.0
# define DEFAULT_AMBIENT_COLOR_G 255.0
# define DEFAULT_AMBIENT_COLOR_B 255.0

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
# define DEFAULT_CAMERA_FOV 70.0

typedef struct s_camera
{
	t_point	pos;				// x,y,z of the camera position: -50.0,0,20
	t_point	dir;				// 3d norm. orientation vector: 0.0,0.0,1.0
	float	fov;				// Horizontal field of view, degrees [0,180]: 70
}			t_camera;

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

/* --------------------- MLX42 constants and structures  ------------------- */

// Default resolutions for window (16:9 aspect ratio):

// 128x72 is the smallest alternative
# define WIDTH_MIN 640
# define HEIGHT_MIN 360
# define WIDTH_DEFAULT 1280	// W = 16/9 * H
# define HEIGHT_DEFAULT 720	// H = 9/16 * W

// Window Title:
# define NAME "Mini Ray Traycer"

# define RGBA 4

/**
 * @brief Structure representing a window data
 * Managed by MLX42 lib
 */
typedef struct s_canvas
{
	mlx_t		*mlx;
	int32_t		width;
	int32_t		height;
	mlx_image_t	*img;
}				t_canvas;

/* -------------------------- Main minirt structure  ----------------------- */

typedef struct s_info
{
	t_ambient_light	ambient;	// Ambient lightning data
	t_camera		camera;		// Camera data
	t_light			*lights;	// Array to store lights on the scene
	size_t			n_lights;	// Amount of lights in the *lights array
	t_object		*objs;		// Array to store scene's objects (sp, pl, cy)
	size_t			n_objs;		// Amount of items in the *objs array
	t_canvas		win;		// mlx window and images info struct
}					t_info;

/* ------------------------- Parser helper structures ----------------------- */

typedef struct s_counter
{
	int	figures;
	int	lights;
	int	camera;
	int	ambient;
}		t_counter;

#endif // MINIRT_DATA_H