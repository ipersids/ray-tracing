/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:41:44 by reerikai          #+#    #+#             */
/*   Updated: 2025/06/02 17:21:28 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	You normalize a vector (tuple) by dividing each of its components by 
	its magnitude.
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
	Dot product takes two vecctors and returns a scalar value. 
	When we start intersecting rays with objects and when we start computing 
	shadings on a surface, dot product will come up. The smaller the dot product,
	the larger the angle between the vectors.
	For example, a dot product of 1 means the vectors are identical and -1 
	means they point in opposite directions.
*/

__attribute__((always_inline)) inline float	dot_product(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/*
	CROSS PRODUCT
	Cross product is a vector operation, that returns a new vector instead 
	of a scalar. The new vector is perpendicular to both of the original 
	vectors.
*/

t_vec3	cross_product(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}
