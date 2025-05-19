/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_base_transform.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:29:30 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/19 14:47:05 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_matrix.h"

t_matrix	translation(float x, float y, float z)
{
	t_matrix	res;

	res = identity();
	res.data[0][3] = x;
	res.data[1][3] = y;
	res.data[2][3] = z;

	return (res);
}

t_matrix	scaling(float x, float y, float z)
{
	t_matrix	res;

	res = identity();
	res.data[0][0] = x;
	res.data[1][1] = y;
	res.data[2][2] = z;

	return (res);
}

t_matrix	rotation_x(float radians)
{
	t_matrix	res;

	res = identity();
	res.data[1][1] = cos(radians);
	res.data[2][1] = -sin(radians);
	res.data[1][2] = sin(radians);
	res.data[2][2] = cos(radians);

	return (res);
}

t_matrix	rotation_y(float radians)
{
	t_matrix	res;

	res = identity();
	res.data[0][0] = cos(radians);
	res.data[0][2] = sin(radians);
	res.data[2][0] = -sin(radians);
	res.data[2][2] = cos(radians);

	return (res);
}

t_matrix	rotation_z(float radians)
{
	t_matrix	res;

	res = identity();
	res.data[0][0] = cos(radians);
	res.data[0][1] = -sin(radians);
	res.data[1][0] = sin(radians);
	res.data[1][1] = cos(radians);

	return (res);
}
