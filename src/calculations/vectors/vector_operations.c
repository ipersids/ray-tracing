/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:41:44 by reerikai          #+#    #+#             */
/*   Updated: 2025/06/01 12:30:14 by ipersids         ###   ########.fr       */
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

t_vec3	addition(t_vec3 vec_a, t_vec3 vec_b)
{
	t_vec3	result;

	result.x = vec_a.x + vec_b.x;
	result.y = vec_a.y + vec_b.y;
	result.z = vec_a.z + vec_b.z;
	return (result);
}

t_vec3	subtraction(t_vec3 vec_a, t_vec3 vec_b)
{
	t_vec3	result;

	result.x = vec_a.x - vec_b.x;
	result.y = vec_a.y - vec_b.y;
	result.z = vec_a.z - vec_b.z;
	return (result);
}

/*
	NEGATION
	Changes for example (4, 2, 5) to (-4, -2, -5)
*/

t_vec3	negation(t_vec3 vec)
{
	t_vec3	result;

	result.x = -vec.x;
	result.y = -vec.y;
	result.z = -vec.z;
	return (result);
}

t_vec3	multiplication(t_vec3 vec, float multiplier)
{
	t_vec3	result;

	result.x = vec.x * multiplier;
	result.y = vec.y * multiplier;
	result.z = vec.z * multiplier;
	return (result);
}

t_vec3	division(t_vec3 vec, float divider)
{
	t_vec3	result;

	result.x = vec.x / divider;
	result.y = vec.y / divider;
	result.z = vec.z / divider;
	return (result);
}
