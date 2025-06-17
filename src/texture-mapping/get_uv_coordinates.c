/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_uv_coordinates.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:02:01 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/17 23:07:59 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief 
 * 
 * Spherical angles:
 * 	- Theta (θ): Horizontal angle around the sphere (longitude)
 * 	- Phi (φ): Vertical angle from top to bottom (latitude)
 * 
 * @param local_point 
 * @param u 
 * @param v 
 */
void	rt_get_spherical_uv(t_sphere *sp, t_point *point, float *u, float *v)
{
	const float	u_rotate = 0.5f;
	float		theta;
	float		phi;
	t_point		local_point;

	local_point = normalize(matrix_multiply_point(sp->inv_transform, *point));
	theta = atan2f(local_point.x, local_point.z) + M_PI;
	phi = acosf(local_point.y);
	*u = 1.0f - (theta / (2 * M_PI));
	*u = fmodf(*u + u_rotate, 1.0f);
	*v = phi / M_PI;
}

t_color	rt_texture_color_at(mlx_image_t *texture, float u, float v)
{
	float		tex_x;
	float		tex_y;
	uint32_t	px_x;
	uint32_t	px_y;
	t_color		color;
	uint32_t	i;

	tex_x = u * texture->width;
	tex_x = fmodf(tex_x, texture->width);
	tex_y = v * texture->height;
	tex_y = fmodf(tex_y,texture->height);
	px_x = (uint32_t)tex_x;
	px_y = (uint32_t)tex_y;
	i = (px_y * texture->width + px_x) * RGBA;
	color.x = texture->pixels[i] / 255.0f;
	color.y = texture->pixels[i + 1] / 255.0f;
	color.z = texture->pixels[i + 2] / 255.0f;
	return (color);
}
