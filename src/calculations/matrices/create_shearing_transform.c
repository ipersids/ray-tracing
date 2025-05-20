/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_shearing_transform.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:48:31 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/20 15:39:28 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Creates a shearing transformation matrix.
 * 
 * Shearing moves each coordinate in proportion to the other two coordinates.
 * The proportions array should contain the following values:
 *   proportions[XY], proportions[XZ], 
 *   proportions[YX], proportions[YZ], 
 *   proportions[ZX], proportions[ZY]
 * where, for example, XY means "move X in proportion to Y".
 * 
 * @param proportions Array of 6 floats: [XY, XZ, YX, YZ, ZX, ZY].
 * @return t_matrix The shearing transformation matrix.
 */
t_matrix	matrix_shearing(float proportions[6])
{
	t_matrix	res;

	res = matrix_identity();
	res.data[0][1] = proportions[XY];
	res.data[0][2] = proportions[XZ];
	res.data[1][0] = proportions[YX];
	res.data[1][2] = proportions[YZ];
	res.data[2][0] = proportions[ZX];
	res.data[2][1] = proportions[ZY];
	return (res);
}
