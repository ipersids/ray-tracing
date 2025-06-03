/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:41:44 by reerikai          #+#    #+#             */
/*   Updated: 2025/06/02 17:06:49 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	POINT 	= A location / point in space
	VECTOR 	= Direction on how to move in space

	Point + Vector = Point
	Vector + Vector = Vector
	Point + Point = INVALID (Trying to add to different points in space)
*/

__attribute__((always_inline)) inline t_vec3
	addition(t_vec3 vec_a, t_vec3 vec_b)
{
	return ((t_vec3){vec_a.x + vec_b.x, vec_a.y + vec_b.y, vec_a.z + vec_b.z});
}

__attribute__((always_inline)) inline t_vec3
	subtraction(t_vec3 vec_a, t_vec3 vec_b)
{
	return ((t_vec3){vec_a.x - vec_b.x, vec_a.y - vec_b.y, vec_a.z - vec_b.z});
}

/*
	NEGATION
	Changes for example (4, 2, 5) to (-4, -2, -5)
*/

__attribute__((always_inline)) inline t_vec3
	negation(t_vec3 vec)
{
	return ((t_vec3){-vec.x, -vec.y, -vec.z});
}

__attribute__((always_inline)) inline t_vec3
	multiplication(t_vec3 vec, float scale)
{
	return ((t_vec3){vec.x * scale, vec.y * scale, vec.z * scale});
}

__attribute__((always_inline)) inline t_vec3
	division(t_vec3 vec, float divider)
{
	return ((t_vec3){vec.x / divider, vec.y / divider, vec.z / divider});
}
