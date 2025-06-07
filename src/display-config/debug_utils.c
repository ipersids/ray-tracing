/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:06:14 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/07 03:33:01 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minirt.h"

void	debug_print_info(t_info *rt)
{
	printf(PRINT_GREEN"INFO:\n"PRINT_DEFAULT);
	printf("\t- capacity_ts: %zu\n", rt->capacity_ts);
	printf("\t- lights: %p\n", rt->lights);
	printf("\t- n_lights: %zu\n", rt->n_lights);
	printf("\t- n_objs: %zu\n", rt->n_objs);
	printf("\t- n_ts: %zu\n", rt->n_ts);
	printf("\t- objs: %p\n", rt->objs);
	printf("\t- ts: %p\n", rt->ts);
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
	printf("\t- FOV: %.2f\n", cam->fov);
	printf("\t- left: %f, %f, %f\n",
		cam->left.x, cam->left.y, cam->left.z);
	printf("\t- true_up: %f, %f, %f\n", cam->true_up.x, cam->true_up.y, cam->true_up.z);
	printf("\t- half_height: %f\n", cam->half_height);
	printf("\t- half_width: %f\n", cam->half_width);
	printf("\t- pixel_size: %f\n", cam->pixel_size);
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
		else if (ELEMENT_CONE == rt->objs[i].id)
			debug_print_co(&rt->objs[i].co);
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


void	debug_print_co(t_cone *co)
{
	printf(PRINT_PURPLE"cone:\n"PRINT_DEFAULT);
	printf("\t- position: %.2f, %.2f, %.2f\n", co->pos.x, co->pos.y, co->pos.z);
	printf("\t- direction: %.2f, %.2f, %.2f\n",
		co->dir.x, co->dir.y, co->dir.z);
	printf("\t- height: %.2f\n", co->height);
	printf("\t- color: %.2f, %.2f, %.2f\n",
		co->color.x, co->color.y, co->color.z);
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
	printf("\t- center: %.2f, %.2f, %.2f\n", sp->center.x, sp->center.y, sp->center.z);
	printf("\t- diameter: %.2f\n", sp->diam);
	printf("\t- radius: %.2f\n", sp->r);
	printf("\t- scale: %.2f\n", sp->scale);
	printf("\t- color: %.2f, %.2f, %.2f\n",
		sp->color.x, sp->color.y, sp->color.z);
}

void	debug_print_world(t_canvas *win)
{
	printf(PRINT_GREEN"\nWORLD:\n"PRINT_DEFAULT);
	printf("\t- window width: %d\n", win->width);
	printf("\t- window height: %d\n", win->height);
	printf("\t- image width: %d\n", win->img->width);
	printf("\t- image height: %d\n", win->img->height);
	printf("\t- world_up: {%.2f, %.2f, %.2f}\n",
		win->world_up.x, win->world_up.y, win->world_up.z);
}

void	debug_print_matrix(t_matrix *m, char *msg)
{
	size_t	row;

	printf(PRINT_PURPLE"\n%s:\n"PRINT_DEFAULT, msg);
	row = 0;
	while (m->dimension > row)
	{
		printf(
			"\t[%f, %f, %f, %f]\n",
			m->data[row][0], m->data[row][1],
			m->data[row][2], m->data[row][3]
		);
		++row;
	}
}

void	debug_print_vector(char *msg, t_vec3 vec)
{
	printf("%s x = %.2f y = %.2f z = %.2f\n", msg, vec.x, vec.y, vec.z);
}
