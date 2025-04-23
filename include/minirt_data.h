/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_data.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:35:35 by ipersids          #+#    #+#             */
/*   Updated: 2025/04/22 15:10:33 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_DATA_H
# define MINIRT_DATA_H

# define EXTENTION ".rt"

/**
 * @brief Colors palette
 */
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define PURPLE "\033[0;35m"
# define DEFAULT "\033[0m"

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
	ELEMENT_CYLINDER
}	t_type;

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}			t_point;

typedef struct s_color
{
	float	r;
	float	g;
	float	b;
}			t_color;

typedef struct s_ambient_light
{
	float	ratio;				// amb. lighting ratio in range [0.0,1.0]: 0.2
	t_color	color;				// R,G,B colors in range [0-255]: 255, 255, 255
}			t_ambient_light;

typedef struct s_camera
{
	t_point	position;			// x,y,z of the camera position: -50.0,0,20
	t_point	direction;			// 3d norm. orientation vector: 0.0,0.0,1.0
	int		fov;				// Horizontal field of view, degrees [0,180]: 70
}			t_camera;

typedef struct s_light
{
	t_point	position;			// x,y,z of the light point: -40.0,50.0,0.0
	float	brightness;			// the light brightness ratio [0.0,1.0]: 0.6
	// t_color	color;			// (unused in mandatory part)
}			t_light;

typedef struct s_sphere
{
	t_point	position;			// x,y,z of sphere center: 0.0,0.0,20.6
	float	diameter;			// the sphere diameter: 12.6
	t_color	color;				// R,G,B colors in range [0-255]: 10, 0, 255
}			t_sphere;

typedef struct s_plane
{
	t_point	position;			// x,y,z of a point on plane: 0.0,0.0,-10.0
	t_point	direction;			// 3d norm. orientation vector: 0.0,1.0,0.0
	t_color	color;				// R,G,B colors in range [0-255]: 0,0,225
}			t_plane;

typedef struct s_cylinder
{
	t_point	position;			// center point of cy. base: 50.0,0.0,20.6
	t_point	direction;			// 3d norm. vector of cy.axis: 0.0,0.0,1.0
	float	diameter;			// the cylinder diameter: 14.2
	float	height;				// the cylinder height: 21.42
	t_color	color;				// R,G,B colors in range [0,255]: 10, 0, 255
}			t_cylinder;

typedef union u_element
{
	t_ambient_light	ambient;
	t_camera		camera;
	t_light			light;
	t_sphere		sphere;
	t_plane			plane;
	t_cylinder		cylinder;
}					t_element;

typedef struct s_object
{
	t_type		id;
	t_element	data;
}				t_object;

#endif // MINIRT_DATA_H