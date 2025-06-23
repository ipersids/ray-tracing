/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_data.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reerikai <reerikai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:26:29 by reerikai          #+#    #+#             */
/*   Updated: 2025/06/23 14:26:30 by reerikai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_DATA_H
# define MINIRT_DATA_H

# include <stdbool.h>			// `bool` data type
# include <limits.h>

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

# define RGBA 4
# define BUMP_FACTOR 0.5f

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
# define MAX_RAY_RECURSION_DEPTH 6

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
	ERR_REALLOC_INTERSECTIONS,
	ERR_EMPTY_SCENE,
	ERR_MATERIAL,
	ERR_PATTERN,
	ERR_BUMP_MAP,
	ERR_MAX
}	t_error;

# define ERR_MODULO ERR_ARGC
# define CAPACITY 20 // initial size of array for reading scene
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
	ELEMENT_UNKNOWN,
	ELEMENT_CYLINDER_CAP,
	ELEMENT_CONE_CAP,
}	t_type;

# define LIMIT_COORD 1000.0f
# define MAX_SIZE 500.0f // size (height, width ...)
# define MIN_SIZE 0.1f // size (height, width ...)

/**
 * @brief Pitch angle limit
 *
 * Prevents the camera from looking straight up or down,
 * which can cause gimbal lock or degenerate view matrices.
 *
 * Fot minimum value used -MAX_PITCH
 */
# define MAX_PITCH_CAMERA 60.0f
# define MAX_PITCH_OBJECT 89.0f
# define Z_DRIFT_DAMPING 1.0f
# define ROTATION_STEP 5.0f
# define LIMIT_S 1000.0f
# define MAX_CONTAINERS 6

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

# define PATTERN_SHIFT 0.01f

typedef enum e_bump_type
{
	BUMP_EARTH,
	BUMP_MARS,
	BUMP_WALL,
	BUMP_MAX
}	t_bump_type;

typedef enum e_texture_type
{
	TEXTURE_SUN,
	TEXTURE_MERCURY,
	TEXTURE_VENUS,
	TEXTURE_EARTH,
	TEXTURE_MARS,
	TEXTURE_JUPITER,
	TEXTURE_SATURN,
	TEXTURE_URANUS,
	TEXTURE_NEPTUNE,
	TEXTURE_PLUTO,
	TEXTURE_MAX
}	t_texture_type;

typedef enum e_pattype
{
	PATTERN_STRIPE,
	PATTERN_STRIPE_OBJ,
	PATTERN_RING,
	PATTERN_RING_OBJ,
	PATTERN_GRADIENT,
	PATTERN_CHECKER,
	PATTERN_CHECKER_OBJ,
	PATTERN_MAX,
	PATTERN_DEFAULT
}			t_pattype;

typedef struct s_pat
{
	t_pattype	type;
	t_color		color_a;
	t_color		color_b;
	t_matrix	transform;
	t_matrix	inv_transform;
	float		scale;
	bool		has_pattern;
}				t_pat;

typedef enum e_mtype
{
	MATERIAL_DEFAULT,
	MATERIAL_LAMBERTIAN,
	MATERIAL_METAL,
	MATERIAL_RUSTED_METAL,
	MATERIAL_GLASS,
	MATERIAL_DIAMOND,
	MATERIAL_PLASTIC,
	MATERIAL_CERAMIC,
	MATERIAL_MIRROR,
	MATERIAL_WATER,
	MATERIAL_ICE,
	MATERIAL_MAX
}	t_mtype;

typedef struct s_material
{
	float	diffuse;			// Light reflected from a surface (0.0-1.0)
	float	specular;			// Bright spot on a surface (0.0-1.0)
	float	shininess;			// Size and sharpness of spec. reflection
	float	reflective;			// 0 non reflective, 1 mirror
	float	refractive;			// index of refraction (1 vacuum, 1.52 glass)
	float	transparency;		// 0 - not allowing light to pass through
}			t_material;

typedef struct s_sphere
{
	t_point		pos;				// x,y,z of sphere center
	float		scale;				// diameter / 2.0f
	t_matrix	inv_transform;
	t_matrix	inv_transpose;
}				t_sphere;

typedef struct s_plane
{
	t_point		pos;				// x,y,z of a point on plane
	t_vec3		dir;				// 3d norm. orientation vector
	t_matrix	inv_transform;
	t_matrix	inv_transpose;
}				t_plane;

typedef struct s_cylinder
{
	t_point		pos;				// center point of cylinder base
	t_vec3		dir;				// 3d norm. vector of cylinder axis
	float		scale;				// diameter / 2.0f
	float		half_height;		// height / 2.0f
	t_matrix	inv_transform;
	t_matrix	inv_transpose;
}				t_cylinder;

typedef struct s_cone
{
	t_point		pos;				// tip position
	t_vec3		dir;				// 3d norm. vector of cone axis
	float		height;
	float		scale;				// scale factor = 1.0f classic cone
	t_matrix	inv_transform;
	t_matrix	inv_transpose;
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
	t_color			color;			// R,G,B colors in range [0.0-1.0]
	t_color			amb_component;	// ambient.intensity * object.color
	t_material		*material;
	t_pat			*pattern;
	bool			has_pattern;
	bool			has_texture;
	bool			has_bump_map;
	t_texture_type	tex_type;
	t_bump_type		bump_type;
}					t_object;

typedef struct s_obj_containter
{
	t_object	*objs[MAX_CONTAINERS];
	int			obj_count;
}				t_obj_container;

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
	float		last_x;
	float		last_y;
	float		yaw;
	float		pitch;
	bool		is_camera;
	bool		is_object;
	t_object	*obj_to_move;
}				t_cursor;

/**
 * @brief Structure representing a window data
 * Managed by MLX42 lib
 */
typedef struct s_window
{
	mlx_t		*mlx;
	int32_t		width;
	int32_t		height;
	t_vec3		world_up;
	bool		rendered;
	bool		resized;
	double		elapsed_time;
	mlx_image_t	*img;
	mlx_image_t	*texture[TEXTURE_MAX];
	mlx_image_t	*bump_map[BUMP_MAX];
	t_cursor	cursor;
}				t_window;

/* ------------------------ Ray and render structures  --------------------- */

typedef enum e_ray_type
{
	RAY_CAMERA,
	RAY_SHADOW,
	RAY_REFLECTION,
	RAY_REFRACTION
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
	t_object		*objs;			// Array to store objects (sp, pl, cy)
	size_t			n_objs;			// Amount of items in the *objs array
	t_window		win;			// mlx window and images info struct
	t_intersection	*ts;			// Intersection collection
	size_t			n_ts;			// Amount t-values in intersection collect
	size_t			capacity_ts;	// Current capacity in intersection collect
	t_pat			patterns[PATTERN_MAX];
	t_material		materials[MATERIAL_MAX];
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
	float		n1;
	float		n2;
	t_object	*obj;
	t_vec3		point;
	t_vec3		under_point;
	t_vec3		eyev;
	t_vec3		normalv;
	t_vec3		reflectv;
	mlx_image_t	*texture;
	t_color		surface_color;
}				t_phong_vars;

typedef struct s_color_at_vars
{
	t_intersection	*t;
	t_color			tmp_color_one;
	t_color			tmp_color_two;
	t_color			tmp_color_surface;
	t_color			surface;
	t_color			reflected;
	t_color			refracted;
	bool			shadowed;
	float			reflectance;
}					t_color_at_vars;

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
}			t_phong_color;

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

typedef struct s_bump_height_vars
{
	float		tex_x;
	float		tex_y;
	uint32_t	px_x;
	uint32_t	px_y;
	uint32_t	i;
	float		height;
}				t_bump_height_vars;

typedef struct s_bump_gradient_vars
{
	float	delta_u;
	float	delta_v;
	float	h_left;
	float	h_right;
	float	h_up;
	float	h_down;
}			t_bump_gradient_vars;

typedef struct t_gradient
{
	float	gradient_u;
	float	gradient_v;
}			t_gradient;

typedef struct s_uv_vars
{
	float	u;
	float	v;
	t_vec3	tangent;
	t_vec3	bitangent;
}			t_uv_vars;

typedef struct s_refract_vars
{
	float	n_ratio;
	float	cos_i;
	float	sin2_t;
	float	cos_t;
}			t_refract_vars;

typedef struct s_in_shadow_vars
{
	float			distance_to_light;
	t_vec3			dir_to_light;
	t_vec3			direction;
	t_ray			shadow_ray;
	t_intersection	*hit;
}					t_in_shadow_vars;

#endif // MINIRT_DATA_H
