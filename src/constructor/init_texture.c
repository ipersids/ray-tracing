/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:17:38 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/21 13:31:32 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

/**
 * @brief Returns the file path for a given texture type.
 * @param texture_type The texture type.
 * @return The file path as a string.
 */
static const char	*get_texture_path(t_texture_type texture_type);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Initializes textures for the window.
 *
 * Loads texture images from disk and converts them for use in rendering.
 * Only runs if IS_BONUS is enabled.
 *
 * @param win Pointer to the window structure.
 * @return 0 on success, or ERR_MLX42 on failure.
 */
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

static const char	*get_texture_path(t_texture_type texture_type)
{
	static const char	list[TEXTURE_MAX][100] = {
		"textures/sun_texture.png",
		"textures/mercury_texture.png",
		"textures/venus_texture.png",
		"textures/eartth_texture.png",
		"textures/mars_texture.png",
		"textures/jupiter_texture.png",
		"textures/saturn_texture.png",
		"textures/uranus_texture.png",
		"textures/neptune_texture.png",
		"textures/pluto_texture.png"
	};

	return (list[texture_type]);
}
