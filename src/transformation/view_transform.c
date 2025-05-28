/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_transform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:00:45 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/28 11:26:44 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief 
 * 
 * @note The inverse transformation could fail in several cases:
 * 		 - Degenerate camera (camera looking at itself)
 * 		 - Zero scaling in any axis (external manipulations)
 * 		 - Floating point precision issues (~1e-15), when matrix appears 
 * 		   invertible but actually isn't numerically stable.
 * 
 * @param cam 
 * @param world_up 
 * @return int 
 */
int	rt_view_transform(t_camera *cam, t_vec3	world_up)
{
	t_matrix	orientation;
	t_matrix	translation;
	t_vec3		norm_forward;

	norm_forward = normalize(cam->forward);
	world_up = normalize(world_up);
	cam->left = cross_product(norm_forward, world_up);
	cam->true_up = cross_product(cam->left, norm_forward);
	orientation = (t_matrix){
		{{cam->left.x, cam->left.y, cam->left.z, 0.0f},
		{cam->true_up.x, cam->true_up.y, cam->true_up.z, 0.0f},
		{-norm_forward.x, -norm_forward.y, -norm_forward.z, 0.0f},
		{0.0f, 0.0f, 0.0f, 1.0f}},
		4
	};
	translation = matrix_translation(-(cam->pos.x), -(cam->pos.y), -(cam->pos.z));
	cam->transform = matrix_multiply(orientation, translation);
	if (false == matrix_try_inverse(cam->transform, &cam->inv_transform))
		return (ERR_CAMERA_NON_INVERSIBLE);
	return (0);
}
