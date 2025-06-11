/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 00:37:12 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/11 15:12:15 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_tests.h"

void	test_cone(void)
{
	printf(PRINT_PURPLE"\n\nTEST CONE SHAPE: \n"PRINT_DEFAULT);

	const float epsilon = 0.0001f;
	t_cone co = {0};
	t_ray ray;
	t_intersections xs;
	t_vec3 normal;

	co.dir = (t_vec3){0.0f,1.0f,0.0f};
	co.height = 1.0f;
	co.scale = 1.0f;
	assert(rt_cone_transform(&co) == 0);

	printf("TEST rt_cone_normal_at(): ");
	t_vec3 check = {0};
	normal = rt_cone_normal_at(&co, (t_point){0.0f, 0.0f, 0.0f});
	check = (t_vec3){0.0f, 0.0f, 0.0f}; // we can't normalize zero-vector
	assert((normal.x - check.x) < epsilon && (normal.y - check.y) < epsilon && (normal.z - check.z) < epsilon);
	normal = rt_cone_normal_at(&co, (t_point){1.0f, 1.0f, 1.0f});
	check = normalize((t_vec3){1.0f, sqrtf(2.0f), 1.0});
	assert((normal.x - check.x) < epsilon && (normal.y - check.y) < epsilon && (normal.z - check.z) < epsilon);
	normal = rt_cone_normal_at(&co, (t_point){-1.0f, -1.0f, 0.0f});
	check = normalize((t_vec3){-1.0f, 1.0, 0.0f});
	assert((normal.x - check.x) < epsilon && (normal.y - check.y) < epsilon && (normal.z - check.z) < epsilon);
	printf(PRINT_GREEN"success\n"PRINT_DEFAULT);

	// C	0,0,-5	0,0,1					40
	// co	0,0,0	0,1,0	1	1	0,0,255
	printf("TEST rt_intersect_cone(): ");
	ray.orig = (t_point){0.0f,0.0f,-5.0f};
	ray.dir = (t_vec3){0.0f,0.0f,1.0f};
	xs = rt_intersect_cone(&co, ray);
	assert(xs.count == 0); // miss
	ray.dir = (t_vec3){0.0f,0.01f,1.0f};
	xs = rt_intersect_cone(&co, ray);
	assert(xs.count == 2);
	printf(PRINT_GREEN"success\n"PRINT_DEFAULT);
}
