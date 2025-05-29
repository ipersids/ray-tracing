#ifndef DISPLAY_CONFIG_H
# define DISPLAY_CONFIG_H

# include <assert.h>

void	debug_print_info(t_info *rt);
void	debug_print_camera(t_camera *camera);
void	debug_print_objects(t_info *rt);
void	debug_print_cy(t_cylinder *cy);
void	debug_print_pl(t_plane *pl);
void	debug_print_sp(t_sphere *sp);
void	debug_print_world(t_canvas *win);
void	debug_print_lights(t_info *rt);
void	debug_print_matrix(t_matrix *m, char *msg);

/// TESTS

void	test_matrix_math(void);
void	test_matrix_transformation(void);
void 	test_camera(void);

#endif // DISPLAY_CONFIG_H