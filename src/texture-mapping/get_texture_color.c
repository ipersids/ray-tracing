/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 23:31:40 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/17 23:58:28 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	rt_texture_color_at(mlx_image_t *texture, float u, float v)
{
	float		tex_x;
	float		tex_y;
	uint32_t	px_x;
	uint32_t	px_y;
	t_color		color;
	uint32_t	i;

	tex_x = fmodf(u * texture->width, texture->width);
	tex_y = fmodf(v * texture->height, texture->height);
	px_x = (uint32_t)tex_x;
	px_y = (uint32_t)tex_y;
	i = (px_y * texture->width + px_x) * RGBA;
	color.x = texture->pixels[i] / 255.0f;
	color.y = texture->pixels[i + 1] / 255.0f;
	color.z = texture->pixels[i + 2] / 255.0f;
	return (color);
}
