/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radians.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:10:03 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/20 15:47:35 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Converts degrees to radians.
 * 
 * @param degrees Angle in degrees.
 * @return float Angle in radians.
 */
float	radians(float degrees)
{
	return (degrees * M_PI / 180.0f);
}
