/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_gradient.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 00:49:31 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/18 00:51:49 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	get_height(mlx_image_t *tex, float u, float v);

t_gradient	rt_get_gradient(mlx_image_t *tex, float u, float v)
{
	t_bump_gradient_vars	var;
	t_gradient				res;

	var.delta_u = 1.0f / tex->width;
	var.delta_v = 1.0f / tex->height;
	var.h_center = get_height(tex, u, v);
	var.h_left = get_height(tex, fmaxf(0.0f, u - var.delta_u), v);
	var.h_right = get_height(tex, fminf(1.0f, u + var.delta_u), v);
	var.h_up = get_height(tex, u, fmaxf(0.0f, v - var.delta_v));
	var.h_down = get_height(tex, u, fminf(1.0f, v + var.delta_v));
	res.gradient_u = (var.h_right - var.h_left) / (2.0f * var.delta_u);
	res.gradient_v = (var.h_down - var.h_up) / (2.0f * var.delta_v);
	return (res);
}

static float	get_height(mlx_image_t *tex, float u, float v)
{
	t_bump_height_vars	vars;

	vars.tex_x = fmodf(u * tex->width, tex->width);
	vars.tex_y = fmodf(v * tex->height, tex->height);
	vars.px_x = (uint32_t)vars.tex_x;
	vars.px_y = (uint32_t)vars.tex_y;
	vars.i = (vars.px_y * tex->width + vars.px_x) * RGBA;
	vars.height = tex->pixels[vars.i] / 255.0f;
	return (vars.height);
}