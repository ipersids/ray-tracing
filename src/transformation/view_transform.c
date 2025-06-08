/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_transform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:00:45 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/08 11:52:52 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Computes the view transformation matrix for the camera.
 *
 * Sets up the camera's orientation and position in world space 
 * by constructing a view transformation matrix. The function calculates 
 * the camera's left and true up vectors, builds the orientation matrix, 
 * and combines it with a translation matrix to position the camera. 
 * The inverse of the view matrix is also computed for transforming rays.
 *
 * @note The inverse transformation could fail in several cases:
 *       - Degenerate camera (camera looking at itself)
 *       - Zero scaling in any axis (external manipulations)
 *       - Floating point precision issues (~1e-15), when matrix appears
 *         invertible but actually isn't numerically stable.
 *
 * @param cam Pointer to the camera structure.
 * @param world_up The up direction vector in world space.
 * @return int 0 on success, or an error code if the matrix is not invertible.
 */
int	rt_view_transform(t_camera *cam, t_vec3	world_up)
{
	t_matrix	orientation;
	t_matrix	transl;
	t_matrix	transform;
	t_vec3		left;
	t_vec3		true_up;

	left = cross_product(cam->forward, world_up);
	true_up = cross_product(left, cam->forward);
	orientation = ((t_matrix){
		{{left.x, left.y, left.z, 0.0f},
		{true_up.x, true_up.y, true_up.z, 0.0f},
		{-cam->forward.x, -cam->forward.y, -cam->forward.z, 0.0f},
		{0.0f, 0.0f, 0.0f, 1.0f}}, 4});
	transl = matrix_translation(-(cam->pos.x), -(cam->pos.y), -(cam->pos.z));
	transform = matrix_multiply(orientation, transl);
	if (false == matrix_try_inverse(transform, &cam->inv_transform))
		return (ERR_CAMERA_NON_INVERSIBLE);
	return (0);
}
