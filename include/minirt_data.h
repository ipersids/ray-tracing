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

# ifndef M_PI
#  define M_PI 3.14159265358979323846
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
	ERR_CAMERA_ORIENT_VECTOR,
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

# define DEFAULT_AMBIENT_RATIO 0.2f
# define DEFAULT_AMBIENT_COLOR (t_color){1.0f, 1.0f, 1.0f}

typedef struct s_ambient_light
{
	float	ratio;				// amb. lighting ratio in range [0.0,1.0]
	t_color	color;				// R,G,B colors in range [0.0-1.0]
}			t_ambient_light;

# define DEFAULT_CAMERA_POSITION (t_point){-50.0f, 0.0f, 20.0f}
# define DEFAULT_CAMERA_ORIENTATION (t_vec3){0.0f, 0.0f, 1.0f}
# define DEFAULT_CAMERA_FOV 70.0f
# define CAMERA_SPEED 0.05f
# define CAMERA_FOCAL_LENGTH 1.0f

typedef struct s_camera
{
	t_point	pos;				// x,y,z of the camera position
	t_vec3	forward;			// 3d norm. orientation vector
	float	fov;				// Horizontal field of view, degrees [0.0,180.0]
	t_point	px00_loc;
	t_vec3	px_delta_u;
	t_vec3	px_delta_v;
	t_vec3	up;
	t_vec3	right;
	float	focal_len;
	float	vport_h;
	float	vport_w;
	t_vec3	vport_u;
	t_vec3	vport_v;
	t_vec3	vport_upleft;
}			t_camera;

typedef struct s_light
{
	t_point	pos;				// x,y,z of the light point
	float	bright;				// the light brightness ratio [0.0,1.0]
	t_color	color;				// (unused in mandatory part)
}			t_light;

typedef struct s_sphere
{
	t_point	pos;				// x,y,z of sphere center
	float	diam;				// the sphere diameter
	float	r;					// the sphere radius
	t_color	color;				// R,G,B colors in range [0.0-1.0]
}			t_sphere;

typedef struct s_plane
{
	t_point	pos;				// x,y,z of a point on plane
	t_vec3	dir;				// 3d norm. orientation vector
	t_color	color;				// R,G,B colors in range [0.0-1.0]
}			t_plane;

typedef struct s_cylinder
{
	t_point	pos;				// center point of cylinder base
	t_vec3	dir;				// 3d norm. vector of cylinder axis
	float	diam;				// the cylinder diameter
	float	r;					// the cylinder radius
	float	height;				// the cylinder height
	t_color	color;				// R,G,B colors in range [0.0,1.0]
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
# define WIDTH_DEFAULT 1280		// W = 16/9 * H
# define HEIGHT_DEFAULT 720		// H = 9/16 * W
# define ASPECT_RATIO 1.777778	// 16/9
# define WORLD_UP (t_vec3){0.0f, 1.0f, 0.0f}

// Window Title:
# define NAME "Mini Ray Traycer"

// # define RGBA 4

/**
 * @brief Structure representing a window data
 * Managed by MLX42 lib
 */
typedef struct s_canvas
{
	mlx_t		*mlx;
	int32_t		width;
	int32_t		height;
	float		a_ratio;
	t_vec3		world_up;
	bool		rendered;
	mlx_image_t	*img;
}				t_canvas;

/* ------------------------ Ray and render structures  --------------------- */

typedef enum e_ray_type
{
	RAY_CAMERA,
}	t_ray_type;

typedef struct s_ray
{
	t_point		orig;
	t_vec3		dir;
	t_ray_type	type;
}				t_ray;

typedef struct s_intersection
{
	float		t;
	t_object	object;
}			t_intersection;


typedef struct s_intersections
{
	t_intersection	t_values[2];
	int				count;
}			t_intersections;

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
