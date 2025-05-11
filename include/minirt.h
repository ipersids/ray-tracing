/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:15:50 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/12 02:18:52 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @todo:
 * 
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

/* ----------------------------- Initialisation  --------------------------- */

void	rt_init_info(t_info *rt);
int		rt_init_objects(t_counter *cnt, t_info *rt);
int		rt_init_canvas(t_info *rt);

/* ------------------------- Validation and Parsing  ----------------------- */

int		rt_validate_input(int argc, char **argv, t_info *rt);
int		rt_read_scene(int fd, char ***content);
int		rt_parse_scene(t_info *rt, char **scene);
int		rt_parse_ambient(t_info *rt, char *line);
int		rt_parse_camera(t_info *rt, char *line);
int		rt_parse_light(t_info *rt, char *line);
int		rt_parse_cylinder(t_info *rt, char *line);
int		rt_parse_plane(t_info *rt, char *line);
int		rt_parse_sphere(t_info *rt, char *line);

/// parser_utils.c

int		rt_parse_float(float *value, char **startptr, char **endptr);
int		rt_parse_color(t_color *color, char **start, char **endptr);
int		rt_parse_coord(t_point *pos, char **start, char **endptr, bool is_norm);
int		rt_validate_end_of_line(char **startptr, char **endptr);

/* ---------------------- Error and memory management ---------------------- */

void	rt_perror(int exit_code);
void	rt_free_arr(void **arr, int i);
void	rt_destroy_exit(t_info *rt, int exit_code);

/* ------------------------- Canvas: MLX42 managment ------------------------ */

void	rt_press_esc_hook(void *param);
void	rt_close_window_hook(void *param);

#endif // MINIRT_H