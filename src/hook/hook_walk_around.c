/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_walk_around.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:52:44 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/08 12:27:10 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

/// @brief Moves or resets the camera forward.
static void	move_forward(t_info *rt, t_camera *cam);

/// @brief Moves the camera backward.
static void	move_backward(t_info *rt, t_camera *cam);

/// @brief Shifts the camera left.
static void	move_left(t_info *rt, t_camera *cam);

/// @brief Shifts the camera right.
static void	move_right(t_info *rt, t_camera *cam);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Handles key events and dispatches movement/reset.
 * 
 * Implements WASD-style camera movement for the ray tracer:
 * Direction depends on where camera is looking
 * 
 *      W (Forward)
 *          ↑
 *          |
 *   A ←----●----→ D
 * (Left)   |    (Right)
 *          ↓
 *      S (Backward)
 *
 * ● = Camera position
 *
 * R - Reset camera to initial position and orientation
 * 
 * @param k Key function callback data.
 * @param param Pointer to the main program structure.
 */
void	rt_key_hook(mlx_key_data_t k, void* param)
{
	t_info		*rt;
	t_camera	*camera;

	rt = (t_info *)param;
 	camera = &rt->camera;
	if (k.key == MLX_KEY_W && (k.action == MLX_PRESS || k.action == MLX_REPEAT))
		move_forward(rt, camera);
	if (k.key == MLX_KEY_S && (k.action == MLX_PRESS || k.action == MLX_REPEAT))
		move_backward(rt, camera);
	if (k.key == MLX_KEY_A && (k.action == MLX_PRESS || k.action == MLX_REPEAT))
		move_left(rt, camera);
	if (k.key == MLX_KEY_D && (k.action == MLX_PRESS || k.action == MLX_REPEAT))
		move_right(rt, camera);
	if (k.key == MLX_KEY_R && (k.action == MLX_PRESS))
		rt_reset_camera(rt);
	if (!rt->win.rendered)
	{
		if (0 != rt_view_transform(&rt->camera, rt->win.world_up))
		{
			ft_putstr_fd("Camera transform failed (walking)\n", STDERR_FILENO);
			rt_destroy_exit(rt, ERR_CAMERA_NON_INVERSIBLE);
		}
	}
}

/* ------------------- Private Function Implementation --------------------- */

static void	move_forward(t_info *rt, t_camera *cam)
{
	t_vec3	move_to;

	move_to = multiplication(cam->forward, CAMERA_SPEED);
	cam->pos = (t_point)addition(cam->pos, move_to);
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
	t_vec3	left;

	left = cross_product(cam->forward, rt->win.world_up);
	left = normalize(left);
	move_to = multiplication(left, CAMERA_SPEED / 2.0f);
	cam->pos = (t_point)addition(cam->pos, move_to);
	rt->win.rendered = false;
}

static void	move_right(t_info *rt, t_camera *cam)
{
	t_vec3	move_to;
	t_vec3	left;

	left = cross_product(cam->forward, rt->win.world_up);
	left = normalize(left);
	move_to = multiplication(left, CAMERA_SPEED / 2.0f);
	cam->pos = (t_point)subtraction(cam->pos, move_to);
	rt->win.rendered = false;
}
