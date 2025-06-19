/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:17:38 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/19 13:32:08 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static const char*	get_texture_path(t_texture_type texture_type);

/* --------------------------- Public Functions ---------------------------- */

int	rt_init_texture(t_window *win)
{
	mlx_texture_t	*texture;
	size_t			i;

	if (!IS_BONUS)
		return (0);
	i = 0;
	while (i < TEXTURE_MAX)
	{
		texture = mlx_load_png(get_texture_path(i));
		if (!texture)
			return (ERR_MLX42);
		win->texture[i] = mlx_texture_to_image(win->mlx, texture);
		mlx_delete_texture(texture);
		if (!win->texture[i])
			return (ERR_MLX42);
		++i;
	}
	return (0);
}

/* ------------------- Private Function Implementation --------------------- */

static const char*	get_texture_path(t_texture_type texture_type)
{
	static const char	list[TEXTURE_MAX][100] = {
		"textures/eartth_texture.png",
		"textures/mars_texture.png",
		"textures/painted-white-bricks_ao.png"
	};

	return (list[texture_type]);
}
