/**
 * @note:
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
# include "minirt_renderer.h"	// camera, ray, colors related functions

/* ----------------------------- Initialisation  --------------------------- */
/// @dir src/constructor

void	rt_init_info(t_info *rt);
int		rt_init_objects(t_counter *cnt, t_info *rt);
int		rt_init_canvas(t_info *rt);

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
t_vec3	subtractation(t_vec3 vec_a, t_vec3 vec_b);
t_vec3	negation(t_vec3 vec);
t_vec3	multiplication(t_vec3 vec, float multiplier);
t_vec3	division(t_vec3 vec, float divider);
t_vec3	normalize(t_vec3 vec);
t_vec3	cross_product(t_vec3 a, t_vec3 b);
t_vec3	multiply_colors(t_vec3 a, t_vec3 b);

float	magnitude(t_vec3 vec);
float	dot_product(t_vec3 a, t_vec3 b);

/* ------------------------- Canvas: MLX42 managment ------------------------ */
/// @dir src/hook
/// @file src/hook/hook_close_window.c

void	rt_press_esc_hook(void *param);
void	rt_close_window_hook(void *param);

#endif // MINIRT_H
