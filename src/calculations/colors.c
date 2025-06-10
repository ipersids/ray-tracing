/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:34:04 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/09 20:48:03 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Multiplies two colors component-wise.
 *
 * @param a First color.
 * @param b Second color.
 * @return t_color The resulting color.
 */
__attribute__((always_inline)) inline t_color
	multiply_colors(t_color a, t_color b)
{
	return ((t_color){a.x * b.x, a.y * b.y, a.z * b.z});
}

/**
 * @brief Multiplies a color by a scalar.
 *
 * @param a The color.
 * @param scalar The scalar value.
 * @return t_color The resulting color.
 */
__attribute__((always_inline)) inline t_color
	multiply_color_scalar(t_color a, float scalar)
{
	return ((t_color){a.x * scalar, a.y * scalar, a.z * scalar});
}

/**
 * @brief Converts a color in the range [0.0, 1.0] to 0xRRGGBBAA format.
 *
 * The function clamps the color components (x, y, z) to the range [0.0, 1.0],
 * scales them to [0, 255], and packs them into a 32-bit integer in the format
 * 0xRRGGBBAA, where alpha (A) is always set to 255.
 *
 * @param color Pointer to the t_color structure containing RGB values.
 * @return uint32_t The packed color in 0xRRGGBBAA format.
 */
uint32_t	rt_convert_to_rgba(const t_color *color)
{
	int32_t	r;
	int32_t	g;
	int32_t	b;
	int32_t	a;

	r = (int32_t)(clampf(color->x, 0.0f, 1.0f) * 255.0f);
	g = (int32_t)(clampf(color->y, 0.0f, 1.0f) * 255.0f);
	b = (int32_t)(clampf(color->z, 0.0f, 1.0f) * 255.0f);
	a = 255;
	return ((r << 24) | (g << 16) | (b << 8) | a);
}
