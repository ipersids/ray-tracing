/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:10:03 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/20 00:18:15 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

__attribute__((always_inline)) inline bool	equal(float a, float b)
{
	return (fabs(a - b) < 0.00001f);
}

/**
 * @brief Converts degrees to radians.
 * 
 * @param degrees Angle in degrees.
 * @return float Angle in radians.
 */
__attribute__((always_inline)) inline float	radians(float degrees)
{
	return (degrees * M_PI / 180.0f);
}

/**
 * @brief Swaps two float values.
 * @param t1 Pointer to the first float.
 * @param t2 Pointer to the second float.
 */
__attribute__((always_inline)) inline void	swapf(float *t1, float *t2)
{
	float	tmp;

	tmp = *t1;
	*t1 = *t2;
	*t2 = tmp;
}

/**
 * @brief Clamps a float value to a specified range [min, max].
 *
 * @param n The value to clamp.
 * @param min The minimum allowable value.
 * @param max The maximum allowable value.
 * @return float The clamped value.
 */
__attribute__((always_inline)) inline float
	clampf(float n, float min, float max)
{
	if (n < min)
		return (min);
	if (n > max)
		return (max);
	return (n);
}
