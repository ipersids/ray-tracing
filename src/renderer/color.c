/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:30:20 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/13 11:59:36 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline float	rt_clampf(float n, float min, float max);

// Packs clamped color in range [0.0, 1.0] into 0xRRGGBBAA format
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

static inline float	rt_clampf(float n, float min, float max)
{
	if (n < min)
		return (min);
	if (n > max)
		return (max);
	return (n);
}
