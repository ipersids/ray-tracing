/**
 * @note (project status)
 * - src/parser/rt_parse_camera.c currently allowing only WORLD_UP at y-axis
 * - src/parser/rt_parse_sphere.c sphere diam currently could not be less then (2.0 * EPSILON)
 * - decide to give error or normalized with warning in case normal.magnitude() != 1.0;
 * 	 for now: addede normalize in transform.
 * - for now we support comments with `#` at the end line in the scene file config
 * - unused rotations in src/calculations/matrices/create_base_transform.c
 * - src/constructor/init_objects.c: allocations for intersections should change when 
 * 	 cylinders will be added
 * 
 * @note (recourses):
 * - lightning model: https://learnopengl.com/Lighting/Basic-Lighting
 * - Physically Based Rendering: From Theory to Implementation:
 *   https://pbr-book.org/4ed/contents (advanced)
 * - The Cherno Ray Tracing youtube playlist
 *   https://www.youtube.com/playlist?list=PLlrATfBNZ98edc5GshdBtREv5asFW3yXl
 * - Welcome to Computer Graphics: https://scratchapixel.com/
 */

#ifndef MINIRT_H
# define MINIRT_H

# include <MLX42/MLX42.h>
# include "libft.h"

# include <math.h>
# include <fcntl.h>				// open
# include <stdio.h>				// perror, printf
# include <string.h>			// strerror
# include <errno.h>				// strerror dependency
# include <unistd.h>			// close, write, read
# include <stdlib.h>			// malloc, free, exit
# include <stdbool.h>			// `bool` data type

# include "minirt_data.h"		// custom data structures and constants
# include "minirt_matrix.h"		// matrices math library
# include "minirt_renderer.h"	// camera, ray, colors related functions

# include "display_config.h"	// debug print objects config

/* ----------------------------- Initialisation  --------------------------- */
/// @dir src/constructor

void	rt_init_info(t_info *rt);
int		rt_init_objects(t_counter *cnt, t_info *rt);
int		rt_init_canvas(t_info *rt);
t_material	rt_init_material(t_color ambient, t_color obj_color, t_mtype type);

/* ------------------------- Validation and Parsing  ----------------------- */
/// @dir src/parser

int		rt_validate_input(int argc, char **argv, t_info *rt);
int		rt_read_scene(int fd, char ***content);
int		rt_parse_scene(t_info *rt, char **scene);
int		rt_parse_ambient(t_info *rt, char *line);
int		rt_parse_camera(t_info *rt, char *line);
int		rt_parse_light(t_info *rt, char *line);
int		rt_parse_cylinder(t_info *rt, char *line);
int		rt_parse_plane(t_info *rt, char *line);
int		rt_parse_sphere(t_info *rt, char *line);
int		rt_set_transformations(t_info *rt);
void	rt_set_material(t_color ambient, t_object *obj, t_mtype type);

/// @file src/parser/parser_utils.c

int		rt_parse_float(float *value, char **startptr, char **endptr);
int		rt_parse_color(t_color *color, char **start, char **endptr);
int		rt_parse_coord(t_point *pos, char **start, char **endptr, bool is_norm);
int		rt_validate_end_of_line(char **startptr, char **endptr);

/* ---------------------- Error and memory management ---------------------- */
/// @dir src/destructor

void	rt_perror(int exit_code);
void	rt_free_arr(void **arr, int i);
void	rt_destroy_exit(t_info *rt, int exit_code);

/* ------------------------------ Calculations ----------------------------- */

bool	equal(float a, float b);
t_vec3	addition(t_vec3 vec_a, t_vec3 vec_b);
t_vec3	subtraction(t_vec3 vec_a, t_vec3 vec_b);
t_vec3	negation(t_vec3 vec);
t_vec3	multiplication(t_vec3 vec, float multiplier);
t_vec3	division(t_vec3 vec, float divider);
t_vec3	normalize(t_vec3 vec);
t_vec3	cross_product(t_vec3 a, t_vec3 b);

t_color	multiply_colors(t_color a, t_color b);
t_color	multiply_color_scalar(t_color a, float scalar);

float	magnitude(t_vec3 vec);
float	dot_product(t_vec3 a, t_vec3 b);

/* ----------------------------- Transformations ---------------------------- */

int		rt_sphere_transform(t_sphere *sp);
int		rt_plane_transform(t_plane *pl);
int		rt_cylinder_transform(t_cylinder *cy);
int		rt_view_transform(t_camera *cam, t_vec3	world_up);

/* ------------------------- Canvas: MLX42 managment ------------------------ */
/// @dir src/hook
/// @file src/hook/hook_close_window.c

void	rt_press_esc_hook(void *param);
void	rt_close_window_hook(void *param);
void	rt_resize_hook(int32_t width, int32_t height, void *param);
void	rt_render_hook(void *param);

#endif // MINIRT_H
