/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_transform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:00:45 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/03 16:52:48 by ipersids         ###   ########.fr       */
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

	world_up = normalize(world_up);
	cam->left = cross_product(cam->forward, world_up);
	cam->true_up = cross_product(cam->left, cam->forward);
	orientation = ((t_matrix){
		{{cam->left.x, cam->left.y, cam->left.z, 0.0f},
		{cam->true_up.x, cam->true_up.y, cam->true_up.z, 0.0f},
		{-cam->forward.x, -cam->forward.y, -cam->forward.z, 0.0f},
		{0.0f, 0.0f, 0.0f, 1.0f}}, 4});
	transl = matrix_translation(-(cam->pos.x), -(cam->pos.y), -(cam->pos.z));
	cam->transform = matrix_multiply(orientation, transl);
	if (false == matrix_try_inverse(cam->transform, &cam->inv_transform))
		return (ERR_CAMERA_NON_INVERSIBLE);
	return (0);
}
