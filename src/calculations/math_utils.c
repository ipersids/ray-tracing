/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:10:03 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/02 17:23:43 by ipersids         ###   ########.fr       */
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
