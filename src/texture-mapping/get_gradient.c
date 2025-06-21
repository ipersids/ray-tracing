/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_gradient.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 00:49:31 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/21 12:01:29 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static float	get_height(mlx_image_t *tex, float u, float v);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Computes the gradient of a bump map texture at given UV coordinates.
 *
 * @param tex Pointer to the bump map texture image.
 * @param u U coordinate (horizontal, 0.0 to 1.0).
 * @param v V coordinate (vertical, 0.0 to 1.0).
 * @return t_gradient Structure containing the gradient in u and v directions.
 */
t_gradient	rt_get_gradient(mlx_image_t *tex, float u, float v)
{
	t_bump_gradient_vars	var;
	t_gradient				res;

	var.delta_u = 1.0f / tex->width;
	var.delta_v = 1.0f / tex->height;
	var.h_left = get_height(tex, fmaxf(0.0f, u - var.delta_u), v);
	var.h_right = get_height(tex, fminf(1.0f, u + var.delta_u), v);
	var.h_up = get_height(tex, u, fmaxf(0.0f, v - var.delta_v));
	var.h_down = get_height(tex, u, fminf(1.0f, v + var.delta_v));
	res.gradient_u = (var.h_right - var.h_left) * 0.5f / var.delta_u;
	res.gradient_v = (var.h_down - var.h_up) * 0.5f / var.delta_v;
	return (res);
}

/* ------------------- Private Function Implementation --------------------- */
/**
 * @brief Gets the height value from a bump map texture at given UV coord.
 *
 * @param tex Pointer to the bump map texture image.
 * @param u U coordinate (horizontal, 0.0 to 1.0).
 * @param v V coordinate (vertical, 0.0 to 1.0).
 * @return The height value (relative luminance) at the given UV coordinate.
 * @note Relative luminance: https://en.wikipedia.org/wiki/Relative_luminance
 */
static float	get_height(mlx_image_t *tex, float u, float v)
{
	t_bump_height_vars	vars;
	t_color				color;

	vars.tex_x = fmodf(u * (tex->width - 1), tex->width - 1);
	vars.tex_y = fmodf(v * (tex->height - 1), tex->height - 1);
	vars.px_x = (uint32_t)vars.tex_x;
	vars.px_y = (uint32_t)vars.tex_y;
	vars.i = (vars.px_y * tex->width + vars.px_x) * RGBA;
	color.x = tex->pixels[vars.i] / 255.0f;
	color.y = tex->pixels[vars.i + 1] / 255.0f;
	color.z = tex->pixels[vars.i + 2] / 255.0f;
	vars.height = 0.2126f * color.x + 0.7152f * color.y + 0.0722f * color.z;
	return (vars.height);
}
