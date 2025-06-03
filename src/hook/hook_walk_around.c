/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_walk_around.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:52:44 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/03 22:55:57 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	move_forward(t_info *rt, t_camera *cam, bool reset);
static void	move_backward(t_info *rt, t_camera *cam);
static void	move_left(t_info *rt, t_camera *cam);
static void	move_right(t_info *rt, t_camera *cam);

void	rt_key_hook(mlx_key_data_t k, void* param)
{
	t_info		*rt;
	t_camera	*camera;

	rt = (t_info *)param;
 	camera = &rt->camera;
	if (k.key == MLX_KEY_W && (k.action == MLX_PRESS || k.action == MLX_REPEAT))
		move_forward(rt, camera, false);
	if (k.key == MLX_KEY_S && (k.action == MLX_PRESS || k.action == MLX_REPEAT))
		move_backward(rt, camera);
	if (k.key == MLX_KEY_A && (k.action == MLX_PRESS || k.action == MLX_REPEAT))
		move_left(rt, camera);
	if (k.key == MLX_KEY_D && (k.action == MLX_PRESS || k.action == MLX_REPEAT))
		move_right(rt, camera);
	if (k.key == MLX_KEY_R && (k.action == MLX_PRESS))
		move_forward(rt, camera, true);
	if (!rt->win.rendered)
	{
		if (0 != rt_view_transform(&rt->camera, rt->win.world_up))
		{
			ft_putstr_fd("Camera transform failed (walking)\n", STDERR_FILENO);
			rt_destroy_exit(rt, ERR_CAMERA_NON_INVERSIBLE);
		}
	}
}

static void	move_forward(t_info *rt, t_camera *cam, bool reset)
{
	t_vec3	move_to;

	if (reset)
	{
		cam->pos = cam->reset_pos;
		cam->forward = cam->reset_forward;
		cam->fov = cam->reset_fov;
	}
	else
	{
		move_to = multiplication(cam->forward, CAMERA_SPEED);
		cam->pos = (t_point)addition(cam->pos, move_to);
	}
	rt->win.rendered = false;
}

static void	move_backward(t_info *rt, t_camera *cam)
{
	t_vec3	move_to;

	move_to = multiplication(cam->forward, CAMERA_SPEED);
	cam->pos = (t_point)subtraction(cam->pos, move_to);
	rt->win.rendered = false;
}

static void	move_left(t_info *rt, t_camera *cam)
{
	t_vec3	move_to;

	cam->left = cross_product(cam->forward, rt->win.world_up);
	move_to = multiplication(cam->left, CAMERA_SPEED);
	cam->pos = (t_point)addition(cam->pos, move_to);
	rt->win.rendered = false;
}

static void	move_right(t_info *rt, t_camera *cam)
{
	t_vec3	move_to;

	cam->left = cross_product(cam->forward, rt->win.world_up);
	move_to = multiplication(cam->left, CAMERA_SPEED);
	cam->pos = (t_point)subtraction(cam->pos, move_to);
	rt->win.rendered = false;
}
