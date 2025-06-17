/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:17:38 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/17 16:33:08 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static const char*	get_texture_path(t_bump_type texture_type);
static const char*	get_bump_map_path(t_bump_type bump_type);

int	rt_init_bump_texture(t_window *win)
{
	mlx_texture_t	*texture;
	size_t			i;

	if (!IS_BONUS)
		return (0);
	i = 0;
	while (i < BUMP_MAX)
	{
		texture = mlx_load_png(get_texture_path(i));
		if (!texture)
			return (ERR_MLX42);
		win->texture[i] = mlx_texture_to_image(win->mlx, texture);
		if (!win->texture[i])
			return (ERR_MLX42);
		mlx_delete_texture(texture);
		texture = mlx_load_png(get_bump_map_path(i));
		if (!texture)
			return (ERR_MLX42);
		win->bump_map[i] = mlx_texture_to_image(win->mlx, texture);
		if (!win->bump_map[i])
			return (ERR_MLX42);
		mlx_delete_texture(texture);
		++i;
	}
	return (0);
}


static const char*	get_texture_path(t_bump_type texture_type)
{
	static const char	list[BUMP_MAX][100] = {
		"textures/eartth_texture.png"
	};

	return (list[texture_type]);
}

static const char*	get_bump_map_path(t_bump_type bump_type)
{
	static const char	list[BUMP_MAX][100] = {
		"textures/earth_bump.png"
	};

	return (list[bump_type]);
}
