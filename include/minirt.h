/**
 * @note (project status)
 * - src/parser/rt_parse_camera.c currently allowing only word up at y-axis
 * - src/parser/rt_parse_sphere.c sphere diam currently could not be less then
 * 	 (2.0 * EPSILON)
 * - decide to give error or normalized with warning in case 
 * 	 normal.magnitude() != 1.0;
 * 	 Make it consictent.
 * - for now we support comments with `#` at the end line in the scene file
 * - unused rotations in src/calculations/matrices/create_base_transform.c
 * - src/constructor/init_objects.c: allocations for intersections should 
 *   change when cylinders will be added
 * - `yaw` and `pitch` clamped [-60.0, 60.0] in src/hook/hook_rotate_camera.c,
 * 	 could it jump because of src/parser/set_cursor.c ?
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

# include "minirt_data.h"		// custom data structures and constants
# include "minirt_math.h"		// matrices math library
# include "minirt_parser.h"		// scene parcing and validation
# include "minirt_renderer.h"	// camera, ray, colors related functions

# include "display_config.h"	// debug print objects config

/* ----------------------------- Initialisation  --------------------------- */
/// @dir src/constructor

void		rt_init_info(t_info *rt);
int			rt_init_objects(t_counter *cnt, t_info *rt);
int			rt_init_window(t_info *rt);
t_material	rt_init_material(t_color ambient, t_color obj_color, t_mtype type);

/* ----------------------------- Transformations ---------------------------- */

int			rt_sphere_transform(t_sphere *sp);
int			rt_plane_transform(t_plane *pl);
int			rt_cylinder_transform(t_cylinder *cy);
int			rt_cone_transform(t_cone *co);
int			rt_view_transform(t_camera *cam, t_vec3	world_up);

/* ---------------------- Error and memory management ---------------------- */
/// @dir src/destructor

void		rt_perror(int exit_code);
void		rt_free_arr(void **arr, int i);
void		rt_destroy_exit(t_info *rt, int exit_code);

/* ------------------------- Window: MLX42 managment ------------------------ */
/// @dir src/hook

void		rt_press_esc_hook(void *param);
void		rt_close_window_hook(void *param);
void		rt_resize_hook(int32_t width, int32_t height, void *param);
void		rt_render_hook(void *param);
void		rt_cursor_hook(double xpos, double ypos, void *param);
void		rt_mouse_hook(mouse_key_t k, action_t a, modifier_key_t m, void *p);
void		rt_scroll_hook(double xdelta, double ydelta, void *param);
void		rt_key_hook(mlx_key_data_t k, void* param);

#endif // MINIRT_H
