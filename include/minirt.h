/**
 * @note (project status)
 * - for now we support comments with `#` at the end line in the scene file
 * - add lite world intersection version (used in src/hook/hook_handle_mouse.c)
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
int			rt_allocate_memory(t_counter *cnt, t_info *rt);
int			rt_init_window(t_info *rt);
void		rt_init_cursor(t_info *rt);

t_material	init_default_material(void);

/* ----------------------------- Transformations ---------------------------- */

int			rt_sphere_transform(t_sphere *sp);
int			rt_plane_transform(t_plane *pl);
int			rt_cylinder_transform(t_cylinder *cy);
int			rt_cone_transform(t_cone *co);
int			rt_view_transform(t_camera *cam, t_vec3	world_up);

int			rt_update_transform(t_info *rt, void *obj, t_type id);

/* ------------------------ Materials and patterns ------------------------- */

t_material	init_default_material(void);
t_material	init_lambertian_material(void);
t_material	init_plastic_material(void);
t_material	init_metal_material(void);
t_material	init_rasted_metal_material(void);
t_material	init_ceramic_material(void);
t_material	init_mirror_material(void);
t_material	init_glass_material(void);
t_material	init_diamond_material(void);
t_material	init_water_material(void);
t_material	init_ice_material(void);

// t_pat	set_stripe_pattern(t_color a, t_color b, float scale, float angle_rad);
// t_pat	set_checker_pattern(t_color a, t_color b, float scale);
// t_pat	set_gradient_pattern(t_color a, t_color b, float scale);
t_pat		set_stripe_pattern(void);
t_pat		set_checker_pattern(void);
t_pat		set_gradient_pattern(void);

t_color		pattern_at_object(t_pat pattern, t_object obj, t_point w_point);
t_color		stripe_pattern_at(t_pat pattern, t_point point);
t_color		gradient_pattern_at(t_pat pattern, t_point point);
t_color		checker_pattern_at(t_pat pattern, t_point point);
// t_color		radiant_gradient_pattern_at(t_pat pattern, t_point point);
// t_color		ring_pattern_at(t_pat pattern, t_point point);

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

void		rt_rotate_camera(t_info *rt, t_cursor *cursor, double x, double y);
void		rt_move_camera(t_info *rt, mlx_key_data_t *key);
void		rt_move_object(t_info *rt, t_cursor *cursor, double x, double y);
void		rt_rotate_object(t_info *rt, t_object *obj, mlx_key_data_t *key);
void		rt_scale_object(t_info *rt, t_object *obj, mlx_key_data_t *key);

t_point		rt_get_ray_based_move(t_info *rt, t_point pos, float dx, float dy);
t_point		rt_get_depth_based_move(t_info *rt, t_point pos, float dy);

#endif // MINIRT_H
