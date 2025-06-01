/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:34:04 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/01 12:47:06 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

/**
 * @brief Clamps a float value to a specified range [min, max].
 * 
 * @param n The value to clamp.
 * @param min The minimum allowable value.
 * @param max The maximum allowable value.
 * @return float The clamped value.
 */
static inline float	rt_clampf(float n, float min, float max);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Multiplies two colors component-wise.
 *
 * @param a First color.
 * @param b Second color.
 * @return t_color The resulting color.
 */
t_color	multiply_colors(t_color a, t_color b)
{
	t_color	result;

	result.x = a.x * b.x;
	result.y = a.y * b.y;
	result.z = a.z * b.z;
	return (result);
}

/**
 * @brief Multiplies a color by a scalar.
 *
 * @param a The color.
 * @param scalar The scalar value.
 * @return t_color The resulting color.
 */
t_color	multiply_color_scalar(t_color a, float scalar)
{
	t_color	result;

	result.x = a.x * scalar;
	result.y = a.y * scalar;
	result.z = a.z * scalar;
	return (result);
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

	r = (int32_t)(rt_clampf(color->x, 0.0f, 1.0f) * 255.0f);
	g = (int32_t)(rt_clampf(color->y, 0.0f, 1.0f) * 255.0f);
	b = (int32_t)(rt_clampf(color->z, 0.0f, 1.0f) * 255.0f);
	a = 255;
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

/* ------------------- Private Function Implementation --------------------- */

static inline float	rt_clampf(float n, float min, float max)
{
	if (n < min)
		return (min);
	if (n > max)
		return (max);
	return (n);
}
