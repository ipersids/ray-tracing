/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 01:37:14 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/08 12:42:25 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void test_camera(void) {
	t_camera cam = {0};
	t_canvas win = {0};
	t_ray ray = {0};
	t_matrix transform;

	printf(PRINT_PURPLE"\n\nTEST CAMERA SETUP: \n"PRINT_DEFAULT);

	printf("TEST rt_camera_init(): ");
	cam.fov = 90.0;
	cam.pos = (t_vec3){0.0, 0.0, 0.0};
	win.width = 200;
	win.height = 125;
	win.world_up = (t_vec3){0.0, 1.0, 0.0};
	cam.forward = subtraction((t_vec3){0.0, 0.0, -1.0}, cam.pos);
	cam.forward = normalize(cam.forward);
	rt_camera_init(&cam, &win);
	assert(equal(cam.pixel_size, 0.01f));
	win.width = 125;
	win.height = 200;
	rt_camera_init(&cam, &win);
	assert(equal(cam.pixel_size, 0.01f));
	printf(PRINT_GREEN"success\n"PRINT_DEFAULT);

	printf("TEST rt_view_transform(): ");
	rt_view_transform(&cam, win.world_up);
	assert(matrix_try_inverse(cam.inv_transform, &transform));
	assert(matrix_equality(transform, matrix_identity()));
	cam.forward = subtraction((t_vec3){0.0, 0.0, 1.0}, cam.pos);
	cam.forward = normalize(cam.forward);
	rt_view_transform(&cam, win.world_up);
	assert(matrix_try_inverse(cam.inv_transform, &transform));
	assert(matrix_equality(transform, matrix_scaling(-1.0, 1.0, -1.0)));
	cam.pos = (t_vec3){0.0, 0.0, 8.0};
	cam.forward = subtraction((t_vec3){0.0, 0.0, 0.0}, cam.pos);
	cam.forward = normalize(cam.forward);
	rt_view_transform(&cam, win.world_up);
	assert(matrix_try_inverse(cam.inv_transform, &transform));
	assert(matrix_equality(transform, matrix_translation(0.0, 0.0, -8.0)));
	cam.pos = (t_vec3){1.0, 3.0, 2.0};
	cam.forward = subtraction((t_vec3){4.0, -2.0, 8.0}, cam.pos);
	cam.forward = normalize(cam.forward);
	win.world_up = normalize((t_vec3){1.0, 1.0, 0.0});
	rt_view_transform(&cam, win.world_up);
	assert(matrix_try_inverse(cam.inv_transform, &transform));
	t_matrix m = {
		{
			{-0.50709, 0.50709, 0.67612, -2.36643},
			{0.76772, 0.60609, 0.12122, -2.82843},
			{-0.35857, 0.59761, -0.71714, 0.00000},
			{0.00000, 0.00000, 0.00000, 1.00000}
		},
		4
	};
	assert(matrix_equality(transform, m));
	printf(PRINT_GREEN"success\n"PRINT_DEFAULT);

	printf("TEST rt_get_ray(): ");
	cam.pos = (t_vec3){0.0, 0.0, 0.0};
	cam.forward = subtraction((t_vec3){0.0, 0.0, -1.0}, cam.pos);
	cam.forward = normalize(cam.forward);
	win.width = 201;
	win.height = 101;
	win.world_up = (t_vec3){0.0, 1.0, 0.0};
	rt_camera_init(&cam, &win);
	rt_view_transform(&cam, win.world_up);
	ray = rt_get_ray(&cam, 100, 50);
	assert(equal(ray.orig.x, 0.0) && equal(ray.orig.y, 0.0) && equal(ray.orig.z, 0.0));
	assert(equal(ray.dir.x, 0.0) && equal(ray.dir.y, 0.0) && equal(ray.dir.z, -1.0));
	ray = rt_get_ray(&cam, 0, 0);
	assert(equal(ray.orig.x, 0.0) && equal(ray.orig.y, 0.0) && equal(ray.orig.z, 0.0));
	assert(equal(ray.dir.x, 0.66519) && equal(ray.dir.y, 0.33259) && equal(ray.dir.z, -0.66851));
	transform = matrix_multiply(matrix_rotation_y(M_PI / 4.0), matrix_translation(0.0, -2.0, 5.0));
	assert(matrix_try_inverse(transform, &cam.inv_transform));
	ray = rt_get_ray(&cam, 100, 50);
	assert(equal(ray.orig.x, 0.0) && equal(ray.orig.y, 2.0) && equal(ray.orig.z, -5.0));
	assert(equal(ray.dir.x, sqrtf(2.0) / 2.0) && equal(ray.dir.y, 0.0) && equal(ray.dir.z, -(sqrtf(2.0) / 2.0)));
	t_matrix tmp = transform;
	cam.pos = (t_vec3){0.0, 2.0, -5.0};
	cam.forward = (t_vec3){0.707, 0, -0.707};
	cam.forward = normalize(cam.forward);
	cam.fov = 90.0;
	rt_camera_init(&cam, &win);
	rt_view_transform(&cam, win.world_up);
	assert(matrix_try_inverse(cam.inv_transform, &transform));
	ray = rt_get_ray(&cam, 100, 50);
	assert(equal(ray.orig.x, 0.0) && equal(ray.orig.y, 2.0) && equal(ray.orig.z, -5.0));
	assert(equal(ray.dir.x, sqrtf(2.0) / 2.0) && equal(ray.dir.y, 0.0) && equal(ray.dir.z, -(sqrtf(2.0) / 2.0)));
	assert(matrix_equality(tmp, transform));
	printf(PRINT_GREEN"success\n"PRINT_DEFAULT);
}