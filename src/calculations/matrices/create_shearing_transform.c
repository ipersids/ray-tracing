/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_chaining_transform.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:48:31 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/19 15:09:20 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_matrix.h"

t_matrix	shearing(float proportions[6])
{
	t_matrix	res;

	res = identity();
	res.data[0][1] = proportions[XY];
	res.data[0][2] = proportions[XZ];
	res.data[1][0] = proportions[YX];
	res.data[1][2] = proportions[YZ];
	res.data[2][0] = proportions[ZX];
	res.data[2][1] = proportions[ZY];
	return (res);
}

