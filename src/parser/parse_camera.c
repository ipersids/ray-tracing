/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:49:52 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/12 12:59:38 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static int	parse_direction(t_info *rt, char **line, char **next);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Parse camera settings from a string.
 * 
 * @param rt Pointer to the ray tracing information structure.
 * @param line The input line containing camera data.
 * @return int 0 on success, or an error code.
 * 
 * @note Camera parsing could fail in several cases:
 * 		 - Camera from and to positions are the same (look at itself)
 * 		 - Camera forward and world up vectors are parallel (gimbal lock)
 * 		 - Values exceeded their limits (ex. 0.0-1.0 for normalized vectors)
 * 		 - Camera pitch angle is outside the range ±60 degrees
 */
int	rt_parse_camera(t_info *rt, char *line)
{
	char	*next;
	int		exit_code;

	next = NULL;
	exit_code = 0;
	exit_code = rt_parse_coord(&rt->camera.pos, &line, &next, false);
	if (0 != exit_code)
		return (exit_code);
	exit_code = parse_direction(rt, &line, &next);
	if (0 != exit_code)
		return (exit_code);
	exit_code = rt_parse_float(&rt->camera.fov, &line, &next);
	if (0 != exit_code || 0 != rt_validate_end_of_line(&line))
		return (ERR_OBJECT_CONFIG);
	if (0.0 > rt->camera.fov || 180.0 < rt->camera.fov)
		return (ERR_OBJECT_CONFIG_LIMITS);
	exit_code = rt_update_transform(rt, NULL, ELEMENT_CAMERA);
	if (0 != exit_code)
		return (exit_code);
	rt_init_cursor(rt);
	rt_save_camera_settings(&rt->camera);
	return (exit_code);
}

/* ------------------- Private Function Implementation --------------------- */

static int	parse_direction(t_info *rt, char **line, char **next)
{
	int		exit_code;

	exit_code = 0;
	exit_code = rt_parse_coord(&rt->camera.forward, line, next, true);
	if (0 != exit_code)
		return (exit_code);
	if (equal(magnitude(rt->camera.forward), 0.0f))
		return (ERR_CAMERA_ORIENT_VECTOR);
	rt->camera.forward = normalize(rt->camera.forward);
	if (fabs(dot_product(rt->camera.forward, rt->win.world_up)) > 0.999f)
		return (ERR_CAMERA_GIMBAL_LOCK);
	if (fabs(asinf(rt->camera.forward.y) * (180.0f / M_PI)) >= MAX_PITCH_CAMERA)
		return (ERR_CAMERA_PITCH_ANGLE);
	while (ft_isspace(**line))
		++(*line);
	return (exit_code);
}
