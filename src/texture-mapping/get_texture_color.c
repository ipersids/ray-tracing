/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 23:31:40 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/21 12:03:47 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

t_color	rt_texture_color_at(mlx_image_t *texture, float u, float v)
{
	float		tex_xy[2];
	uint32_t	px_x;
	uint32_t	px_y;
	t_color		color;
	uint32_t	i;

	tex_xy[0] = fmodf(u * (texture->width - 1), texture->width - 1);
	tex_xy[1] = fmodf(v * (texture->height - 1), texture->height - 1);
	px_x = (uint32_t)tex_xy[0];
	px_y = (uint32_t)tex_xy[1];
	i = (px_y * texture->width + px_x) * RGBA;
	color.x = texture->pixels[i] / 255.0f;
	color.y = texture->pixels[i + 1] / 255.0f;
	color.z = texture->pixels[i + 2] / 255.0f;
	return (color);
}
