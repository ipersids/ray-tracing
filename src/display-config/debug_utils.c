/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:06:14 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/16 01:45:13 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	debug_print_info(t_info *rt)
{
	printf(PRINT_GREEN"AMBIENT:\n"PRINT_DEFAULT);
	printf("\t- ratio: %.2f\n", rt->ambient.ratio);
	printf("\t- color: %.2f, %.2f, %.2f\n",
		rt->ambient.color.x, rt->ambient.color.y, rt->ambient.color.z);
	debug_print_camera(&rt->camera);
	debug_print_lights(rt);
	debug_print_objects(rt);
}

void	debug_print_camera(t_camera *cam)
{
	printf(PRINT_GREEN"\nCAMERA:\n"PRINT_DEFAULT);
	printf("\t- position: %.2f, %.2f, %.2f\n",
		cam->pos.x, cam->pos.y, cam->pos.z);
	printf("\t- forward: %.2f, %.2f, %.2f\n",
		cam->forward.x, cam->forward.y, cam->forward.z);
	printf("\t- FOV: %.2f\n\t- focal_len: %2.f\n", cam->fov, cam->focal_len);
	printf("\t- right: %.2f, %.2f, %.2f\n",
		cam->right.x, cam->right.y, cam->right.z);
	printf("\t- up: %.2f, %.2f, %.2f\n", cam->up.x, cam->up.y, cam->up.z);
	printf("\t- vport_h: %.2f\n", cam->vport_h);
	printf("\t- vport_w: %.2f\n", cam->vport_w);
	printf("\t- vport_u: %.2f, %.2f, %.2f\n",
		cam->vport_u.x, cam->vport_u.y, cam->vport_u.z);
	printf("\t- vport_v: %.2f, %.2f, %.2f\n",
		cam->vport_v.x, cam->vport_v.y, cam->vport_v.z);
	printf("\t- px_delta_u: %.2f, %.2f, %.2f\n",
		cam->px_delta_u.x, cam->px_delta_u.y, cam->px_delta_u.z);
	printf("\t- px_delta_v: %.2f, %.2f, %.2f\n",
		cam->px_delta_v.x, cam->px_delta_v.y, cam->px_delta_v.z);
	printf("\t- vport_upleft: %.2f, %.2f, %.2f\n",
		cam->vport_upleft.x, cam->vport_upleft.y, cam->vport_upleft.z);
	printf("\t- px00_loc: %.2f, %.2f, %.2f\n",
		cam->px00_loc.x, cam->px00_loc.y, cam->px00_loc.z);
}

void	debug_print_lights(t_info *rt)
{
	size_t	i;

	i = 0;
	printf(PRINT_GREEN"\nLIGHTS:\n"PRINT_DEFAULT);
	while (i < rt->n_lights)
	{
		printf("Light [%zu/%zu]:\n", i + 1, rt->n_lights);
		printf("\t- position: %.2f, %.2f, %.2f\n", rt->lights[i].pos.x,
			rt->lights[i].pos.y, rt->lights[i].pos.z);
		printf("\t- brightness: %.2f\n", rt->lights[i].bright);
		printf("\t- color: %.2f, %.2f, %.2f\n", rt->lights[i].color.x,
			rt->lights[i].color.y, rt->lights[i].color.z);
		++i;
	}
}

void	debug_print_objects(t_info *rt)
{
	size_t	i;

	i = 0;
	printf(PRINT_GREEN"\nOBJECTS:\n"PRINT_DEFAULT);
	while (i < rt->n_objs)
	{
		printf("Object [%zu/%zu] -> ", i + 1, rt->n_objs);
		if (ELEMENT_CYLINDER == rt->objs[i].id)
			debug_print_cy(&rt->objs[i].cy);
		else if (ELEMENT_PLANE == rt->objs[i].id)
			debug_print_pl(&rt->objs[i].pl);
		else if (ELEMENT_SPHERE == rt->objs[i].id)
			debug_print_sp(&rt->objs[i].sp);
		else
			printf(PRINT_RED"Uknown object!\n"PRINT_DEFAULT);
		++i;
	}
}

void	debug_print_cy(t_cylinder *cy)
{
	printf(PRINT_PURPLE"cylinder:\n"PRINT_DEFAULT);
	printf("\t- position: %.2f, %.2f, %.2f\n", cy->pos.x, cy->pos.y, cy->pos.z);
	printf("\t- direction: %.2f, %.2f, %.2f\n",
		cy->dir.x, cy->dir.y, cy->dir.z);
	printf("\t- diameter: %.2f\n", cy->diam);
	printf("\t- radius: %.2f\n", cy->r);
	printf("\t- height: %.2f\n", cy->height);
	printf("\t- color: %.2f, %.2f, %.2f\n",
		cy->color.x, cy->color.y, cy->color.z);
}

void	debug_print_pl(t_plane *pl)
{
	printf(PRINT_PURPLE"plane:\n"PRINT_DEFAULT);
	printf("\t- position: %.2f, %.2f, %.2f\n", pl->pos.x, pl->pos.y, pl->pos.z);
	printf("\t- direction: %.2f, %.2f, %.2f\n",
		pl->dir.x, pl->dir.y, pl->dir.z);
	printf("\t- color: %.2f, %.2f, %.2f\n",
		pl->color.x, pl->color.y, pl->color.z);
}

void	debug_print_sp(t_sphere *sp)
{
	printf(PRINT_PURPLE"sphere:\n"PRINT_DEFAULT);
	printf("\t- position: %.2f, %.2f, %.2f\n", sp->pos.x, sp->pos.y, sp->pos.z);
	printf("\t- diameter: %.2f\n", sp->diam);
	printf("\t- radius: %.2f\n", sp->r);
	printf("\t- color: %.2f, %.2f, %.2f\n",
		sp->color.x, sp->color.y, sp->color.z);
}

void	debug_print_world(t_canvas *win)
{
	printf(PRINT_GREEN"\nWORLD:\n"PRINT_DEFAULT);
	printf("\t- window width: %d\n", win->width);
	printf("\t- window height: %d\n", win->height);
	printf("\t- a_ratio: %.2f\n", win->a_ratio);
	printf("\t- image width: %d\n", win->img->width);
	printf("\t- image height: %d\n", win->img->height);
	printf("\t- world_up: {%.2f, %.2f, %.2f}\n",
		win->world_up.x, win->world_up.y, win->world_up.z);
}
