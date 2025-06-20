#ifndef DISPLAY_CONFIG_H
# define DISPLAY_CONFIG_H

#include "minirt.h"

void	debug_print_info(t_info *rt);
void	debug_print_camera(t_camera *camera);
void	debug_print_objects(t_info *rt);
void	debug_print_cy(t_object *obj);
void	debug_print_co(t_object *obj);
void	debug_print_pl(t_object *obj);
void	debug_print_sp(t_object *obj);
void	debug_print_world(t_window *win);
void	debug_print_lights(t_info *rt);
void	debug_print_matrix(t_matrix *m, char *msg);
void	debug_print_vector(char *msg, t_vec3 vec);

#endif // DISPLAY_CONFIG_H