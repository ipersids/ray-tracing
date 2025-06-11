/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 02:48:21 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/11 14:12:26 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

/**
 * @brief Applies movement to the object's position based on input offsets.
 *
 * Determines the object's position pointer by type, then moves it either
 * along the view direction (if Ctrl is held) or in the screen plane.
 * Updates the object's transform after moving.
 *
 * @param rt Pointer to the main program structure.
 * @param obj Pointer to the object to move.
 * @param dx Change in x (screen space).
 * @param dy Change in y (screen space).
 * @return 0 on success, or an error code.
 */
static int	perform_movement(t_info *rt, t_object *obj, double dx, double dy);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Moves the selected object based on mouse movement.
 *
 * Calculates the offset from the last cursor position, updates the cursor,
 * and applies the movement to the selected object. If movement fails,
 * prints an error and exits the program.
 *
 * @param rt Pointer to the main program structure.
 * @param cursor Pointer to the cursor state structure.
 * @param x Current x position of the mouse.
 * @param y Current y position of the mouse.
 */
void	rt_move_object(t_info *rt, t_cursor *cursor, double x, double y)
{
	float	xoffset;
	float	yoffset;
	int		exit_code;

	exit_code = 0;
	xoffset = x - cursor->last_x;
	yoffset = y - cursor->last_y;
	cursor->last_x = x;
	cursor->last_y = y;
	exit_code = perform_movement(rt, cursor->obj_to_move, xoffset, yoffset);
	if (0 != exit_code)
	{
		ft_putstr_fd("Object transform fails (movement):\n", STDERR_FILENO);
		rt_destroy_exit(rt, exit_code);
	}
	rt->win.rendered = false;
}

/* ------------------- Private Function Implementation --------------------- */

static int	perform_movement(t_info *rt, t_object *obj, double dx, double dy)
{
	t_point	*pos;
	int		exit_code;

	pos = NULL;
	exit_code = 0;
	if (ELEMENT_SPHERE == obj->id)
		pos = &obj->sp.pos;
	else if (ELEMENT_PLANE == obj->id)
		pos = &obj->pl.pos;
	else if (ELEMENT_CYLINDER == obj->id)
		pos = &obj->cy.pos;
	else if (IS_BONUS && ELEMENT_CONE == obj->id)
		pos = &obj->co.pos;
	if (!pos)
		return (ERR_OBJECT_TYPE);
	if (mlx_is_key_down(rt->win.mlx, MLX_KEY_LEFT_CONTROL))
		*pos = rt_get_depth_based_move(rt, *pos, dy);
	else
		*pos = rt_get_ray_based_move(rt, *pos, dx, dy);
	exit_code = rt_update_transform(rt, obj, obj->id);
	return (exit_code);
}
