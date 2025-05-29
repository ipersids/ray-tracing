/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:41:44 by reerikai          #+#    #+#             */
/*   Updated: 2025/05/30 01:33:43 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	equal(float a, float b)
{
	float	epsilon;

	epsilon = 0.00001; // Maybe define this in header?
	if (fabs(a - b) < epsilon)
		return (true);
	return (false);
}

/*
	POINT 	= A location / point in space
	VECTOR 	= Direction on how to move in space

	Point + Vector = Point
	Vector + Vector = Vector
	Point + Point = INVALID (Trying to add to different points in space)
*/

t_vec3	addition(t_vec3 vec_a, t_vec3 vec_b)
{
	t_vec3 result;

	result.x = vec_a.x + vec_b.x;
	result.y = vec_a.y + vec_b.y;
	result.z = vec_a.z + vec_b.z;
	return (result);
}

t_vec3	subtraction(t_vec3 vec_a, t_vec3 vec_b)
{
	t_vec3 result;

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

/*
	MAGNITUDE
	The distance represented by a vector is called its magnitude or length.
	It's how far you would travel in a straight line if you were to walk from
	one end of the vector to the other.
	Vectors with magnitude of 1 are called 'unit vectors'.
*/

float	magnitude(t_vec3 vec)
{
	float	sum;

	sum = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
	return (sqrt(sum));
}

/*
	NORMALIZATION
	Normalization is the process of taking an arbitary vector and convering it
	into a unit vector.
	You normalize a vector (tuple) by dividing each of its components by its magnitude.
*/

t_vec3	normalize(t_vec3 vec)
{
	t_vec3	result;
	float	mag;

	mag = magnitude(vec);
	result.x = vec.x / mag;
	result.y = vec.y / mag;
	result.z = vec.z / mag;
	return (result);
}

/*
	DOT PRODUCT
	Dot product takes two vecctors and returns a scalar value. When we start intersecting
	rays with objects and when we start computing shadings on a surface, dot product
	will come up. The smaller the dot product, the larger the angle between the vectors.
	For example, a dot product of 1 means the vectors are identical and -1 means they point
	in opposite directions.
*/

float	dot_product(t_vec3 a, t_vec3 b)
{
	float	result;

	result = a.x * b.x + a.y * b.y + a.z * b.z;
	return (result);
}

/*
	CROSS PRODUCT
	Cross product is a vector operation, that returns a new vector instead of a scalar.
	The new vector is perpendicular to both of the original vectors.
*/

t_vec3	cross_product(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}
