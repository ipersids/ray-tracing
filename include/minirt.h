/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:15:50 by ipersids          #+#    #+#             */
/*   Updated: 2025/04/23 16:44:56 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @todo:
 * 
 * @note:
 * - lightning model: https://learnopengl.com/Lighting/Basic-Lighting
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

# include "minirt_data.h"

/* ----------------------------- Initialisation  --------------------------- */

void	rt_init_info(t_info *rt);

/* --------------------- File and arguments validation  -------------------- */

int		rt_validate_input(int argc, char **argv, t_info *rt);
int		rt_read_scene(int fd, char ***content);

/* ---------------------- Error and memory management ---------------------- */

void	rt_perror(int exit_code);
void	rt_free_arr(void **arr, int i);

#endif // MINIRT_H