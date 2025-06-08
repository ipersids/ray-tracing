#ifndef MINIRT_DATA_H
# define MINIRT_DATA_H

# include <stdbool.h>			// `bool` data type

/* ---------------------------- Vector  strucrtures ------------------------ */

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}			t_vec3;

typedef t_vec3	t_point;
typedef t_vec3	t_color;

/* --------------------------- Matrices strucrtures ------------------------ */

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

typedef struct s_submatrix_var
{
	t_matrix	res;
	size_t		row;
	size_t		col;
	size_t		src_row;
	size_t		src_col;
}				t_subm_var;

/* ------------------- File validation and errors handling  ----------------- */

# define EXTENSION ".rt"

/**
 * @brief Colors palette
 */
# define PRINT_RED "\033[0;31m"
# define PRINT_GREEN "\033[0;32m"
# define PRINT_PURPLE "\033[0;35m"
# define PRINT_DEFAULT "\033[0m"

# ifndef IS_BONUS
#  define IS_BONUS 0
# endif

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define EPSILON 0.00001f
# define SHADOW_BIAS 0.01f

/**
 * @brief Default recursion depth for ray tracing.
 *
 * This constant sets the default number of rays that can be recursively "shot"
 * (e.g., for reflections) when calculating the color at a point.
 */
# define MAX_RAY_RECURSION_DEPTH 5

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
	ERR_OBJECT_ORIENT_VECTOR,
	ERR_CAMERA_GIMBAL_LOCK,
	ERR_CAMERA_PITCH_ANGLE,
	ERR_CAMERA_NON_INVERSIBLE,
	ERR_MATRIX_NON_INVERSIBLE,
	ERROR_REALLOC_INTERSECTIONS,
	ERROR_EMPTY_SCENE,
	ERR_MAX
}	t_error;

# define ERR_MODULO ERR_ARGC
# define CAPACITY 10 // initual size of array for reading scene
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
	ELEMENT_CONE,
	ELEMENT_UKNOWN,
	ELEMENT_CYLINDER_CAP,
	ELEMENT_CONE_CAP,
}	t_type;

# define LIMIT_COORD 1000.0f
# define MAX_SIZE 500.0f // size (height, width ...)
# define MIN_SIZE 0.001f // size (height, width ...)

/**
 * @brief Pitch angle limit
 * 
 * Prevents the camera from looking straight up or down, 
 * which can cause gimbal lock or degenerate view matrices.
 * 
 * Fot minimum value used -MAX_PITCH
 */
# define MAX_PITCH 60.0f

typedef struct s_camera
{
	t_point		pos;				// x,y,z of the camera position
	t_vec3		forward;			// 3d norm. orientation vector
	float		fov;				// Horizontal field of view [0.0,180.0]
	t_matrix	inv_transform;
	float		half_width;
	float		half_height;
	float		pixel_size;
}			t_camera;

typedef struct s_light
{
	t_point	pos;				// x,y,z of the light point
	t_color	intensity;			// multiplication(light.color, light.bright)
}			t_light;

typedef enum e_pattype
{
	PATTERN_STRIPE,
	PATTERN_RING,
	PATTERN_GRADIENT,
	PATTERN_CHECKER,
	PATTERN_RADIANT_GRADIENT
}			t_pattype;

typedef struct	s_pat
{
	t_pattype 	type;
	t_color		color_a;
	t_color		color_b;
	t_matrix	transform;
	t_matrix	inv_transform;
	float		scale;
	bool		has_pattern;
}			t_pat;

typedef enum e_mtype
{
	MATERIAL_DEFAULT,
	MATERIAL_MAX
}	t_mtype;

typedef struct s_material
{
	t_mtype	type;
	t_color	color;				// equal object.color
	t_color	final_color;		// init to ambient_comp from start
	t_color	ambient_comp;		// ambient.intensity * object.color
	float	diffuse;			// Light reflected from a surface (0.0-1.0)
	float	specular;			// Bright spot on a surface (0.0-1.0)
	float	shininess;			// Size and sharpness of spec. reflection
	float	reflective;			// How reflective the material is (0 non reflective, 1 mirror)
	t_pat	pattern;
}			t_material;

typedef struct s_sphere
{
	t_point		pos;				// x,y,z of sphere center
	float		scale;				// diameter / 2.0f
	t_color		color;				// R,G,B colors in range [0.0-1.0]
	t_matrix	inv_transform;
	t_matrix	inv_transpose;
	t_material	material;
}				t_sphere;

typedef struct s_plane
{
	t_point		pos;				// x,y,z of a point on plane
	t_vec3		dir;				// 3d norm. orientation vector
	t_color		color;				// R,G,B colors in range [0.0-1.0]
	t_matrix	inv_transform;
	t_matrix	inv_transpose;
	t_material	material;
}				t_plane;

typedef struct s_cylinder
{
	t_point		pos;				// center point of cylinder base
	t_vec3		dir;				// 3d norm. vector of cylinder axis
	float		scale;				// diameter / 2.0f
	float		half_height;		// height / 2.0f
	t_color		color;				// R,G,B colors in range [0.0,1.0]
	t_matrix	inv_transform;
	t_matrix	inv_transpose;
	t_material	material;
}				t_cylinder;

typedef struct s_cone
{
	t_point		pos;				// tip position
	t_vec3		dir;				// 3d norm. vector of cone axis
	float		height;
	float		scale;				// scale factor = 1.0f classic cone
	t_color		color;				// R,G,B colors in range [0.0,1.0]
	t_matrix	inv_transform;
	t_matrix	inv_transpose;
	t_material	material;
}				t_cone;

typedef struct s_object
{
	t_type			id;
	union
	{
		t_sphere	sp;
		t_plane		pl;
		t_cylinder	cy;
		t_cone		co;
	};
	t_material		*material;
}					t_object;

/* --------------------- MLX42 constants and structures  ------------------- */

// Default resolutions for window (16:9 aspect ratio):

// 128x72 is the smallest alternative
# define WIDTH_MIN 640
# define HEIGHT_MIN 360
# define WIDTH_DEFAULT 1280		// W = 16/9 * H
# define HEIGHT_DEFAULT 720		// H = 9/16 * W
# define ASPECT_RATIO 1.777778	// 16/9

// Window Title:
# define NAME "Mini Ray Traycer"

// # define FPS 0.01666666667 // 1/60
# define FPS 0.03333333333 // 1/30
# define CURSOR_SENSITIVITY 0.05f
# define FOV_ZOOM_SPEED 2.0f
# define FOV_ZOOM_MIN 0.0f
# define FOV_ZOOM_MAX 180.0f
# define CAMERA_SPEED 5.0f

typedef struct s_cursor
{
	float	last_x;
	float	last_y;
	bool	is_first;
	bool	is_dragging;
	float	xoffset;
	float	yoffset;
	float	yaw;
	float	pitch;
}			t_cursor;

/**
 * @brief Structure representing a window data
 * Managed by MLX42 lib
 */
typedef struct s_canvas
{
	mlx_t		*mlx;
	int32_t		width;
	int32_t		height;
	t_vec3		world_up;
	bool		rendered;
	bool		resized;
	double		elapsed_time;
	mlx_image_t	*img;
	t_cursor	cursor;
}				t_canvas;

/* ------------------------ Ray and render structures  --------------------- */

typedef enum e_ray_type
{
	RAY_CAMERA,
	RAY_SHADOW,
	RAY_REFLECTION
}	t_ray_type;

typedef struct s_ray
{
	t_point		orig;
	t_vec3		dir;
	t_ray_type	type;
}				t_ray;

typedef struct s_intersection
{
	float	t;
	size_t	i_object;
	t_type	obj_type;
}			t_intersection;

typedef struct s_intersections
{
	float	t[2];
	size_t	count;
	t_type	obj_type;
}			t_intersections;

typedef struct s_point_light
{
	t_color	intensity;
	t_point	position;
}			t_plight;

/* -------------------------- Main minirt structure  ----------------------- */

typedef struct s_info
{
	t_color			amb_intensity;	// Ambient lightning data
	t_camera		camera;			// Camera data
	t_light			*lights;		// Array to store lights on the scene
	size_t			n_lights;		// Amount of lights in the *lights array
	t_object		*objs;			// Array to store scene's objects (sp, pl, cy)
	size_t			n_objs;			// Amount of items in the *objs array
	t_canvas		win;			// mlx window and images info struct
	t_intersection	*ts;			// Intersection collection
	size_t			n_ts;			// Amount t-values in intersection collection
	size_t			capacity_ts;	// Current capacity in intersection collection
}					t_info;

/* ------------------------- Parser helper structures ----------------------- */

typedef struct s_counter
{
	int	figures;
	int	lights;
	int	camera;
	int	ambient;
}		t_counter;

typedef struct s_phong_vars
{
	float		t;
	t_object	*obj;
	t_vec3		point;
	t_vec3		eyev;
	bool		is_inside;
	t_vec3		normalv;
	t_vec3		reflectv;
}				t_phong_vars;

# define BLACK (t_color){0, 0, 0}
# define WHITE (t_color){1, 1, 1}
# define RED (t_color){1, 0, 0}
# define GREEN (t_color){0, 1, 0}
# define BLUE (t_color){0, 0, 1}

typedef struct s_phong_color
{
	t_color	eff_col;
	t_color	amb;
	t_color	dif;
	t_color	spec;
	t_vec3	lightv;
	t_vec3	reflectv;
	float	l_dot_norm;
	float	refl_dot_eye;
	float	factor;
}				t_phong_color;

typedef struct s_ray_vars
{
	float	xoffset;
	float	yoffset;
	float	world_x;
	float	world_y;
	t_vec3	pixel;
}			t_ray_vars;

typedef struct s_intersect_vars
{
	float	a;
	float	b;
	float	c;
	float	disc;	// discriminant value
	float	t1;
	float	t2;
	float	y0;
	float	y1;
}			t_intersect_vars;

#endif // MINIRT_DATA_H
