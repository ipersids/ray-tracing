/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bump_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:44:06 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/21 10:46:14 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

/**
 * @brief Returns the file path for a given bump map type.
 * @param bump_type The bump map type.
 * @return The file path as a string.
 */
static const char	*get_bump_map_path(t_bump_type bump_type);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Initializes bump maps for the window.
 *
 * Loads bump map textures from disk and converts them to images 
 * for use in rendering. Only runs if IS_BONUS is enabled.
 *
 * @param win Pointer to the window structure.
 * @return 0 on success, or ERR_MLX42 on failure.
 */
int	rt_init_bump_map(t_window *win)
{
	mlx_texture_t	*bump_texture;
	size_t			i;

	if (!IS_BONUS)
		return (0);
	i = 0;
	while (i < BUMP_MAX)
	{
		bump_texture = mlx_load_png(get_bump_map_path(i));
		if (!bump_texture)
			return (ERR_MLX42);
		win->bump_map[i] = mlx_texture_to_image(win->mlx, bump_texture);
		mlx_delete_texture(bump_texture);
		if (!win->bump_map[i])
			return (ERR_MLX42);
		++i;
	}
	return (0);
}

/* ------------------- Private Function Implementation --------------------- */

static const char	*get_bump_map_path(t_bump_type bump_type)
{
	static const char	list[BUMP_MAX][100] = {
		"textures/earth_bump.png",
		"textures/mars_bump.png",
		"textures/painted-white-bricks_height.png"
	};

	return (list[bump_type]);
}
