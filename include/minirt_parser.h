/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_parser.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:10:41 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/06 19:33:21 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_PARSER_H
# define MINIRT_PARSER_H

# include "minirt_data.h"

/// @dir src/parser
/* ------------------------- Validation and Parsing  ----------------------- */

int		rt_validate_input(int argc, char **argv, t_info *rt);
int		rt_read_scene(int fd, char ***content);
int		rt_parse_scene(t_info *rt, char **scene);
int		rt_parse_ambient(t_info *rt, char *line);
int		rt_parse_camera(t_info *rt, char *line);
int		rt_parse_light(t_info *rt, char *line);
int		rt_parse_cylinder(t_info *rt, char *line);
int		rt_parse_cone(t_info *rt, char *line);
int		rt_parse_plane(t_info *rt, char *line);
int		rt_parse_sphere(t_info *rt, char *line);
int		rt_set_transformations(t_info *rt);
void	rt_set_material(t_color ambient, t_object *obj, t_mtype type);
void	rt_set_cursor(t_info *rt);

/// @file src/parser/parser_utils.c

int		rt_parse_float(float *value, char **startptr, char **endptr);
int		rt_parse_color(t_color *color, char **start, char **endptr);
int		rt_parse_coord(t_point *pos, char **start, char **endptr, bool is_norm);
int		rt_validate_end_of_line(char **startptr, char **endptr);

#endif // MINIRT_PARSER_H