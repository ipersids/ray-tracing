/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:06:14 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/11 19:27:13 by ipersids         ###   ########.fr       */
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
	printf("\t- intensity: %.2f, %.2f, %.2f\n",
		rt->amb_intensity.x, rt->amb_intensity.y, rt->amb_intensity.z);
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
		printf("\t- intensity: %.2f, %.2f, %.2f\n", rt->lights[i].intensity.x,
			rt->lights[i].intensity.y, rt->lights[i].intensity.z);
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
			debug_print_cy(&rt->objs[i]);
		else if (ELEMENT_CONE == rt->objs[i].id)
			debug_print_co(&rt->objs[i]);
		else if (ELEMENT_PLANE == rt->objs[i].id)
			debug_print_pl(&rt->objs[i]);
		else if (ELEMENT_SPHERE == rt->objs[i].id)
			debug_print_sp(&rt->objs[i]);
		else
			printf(PRINT_RED"Uknown object!\n"PRINT_DEFAULT);
		++i;
	}
}

void	debug_print_cy(t_object *obj)
{
	printf(PRINT_PURPLE"cylinder:\n"PRINT_DEFAULT);
	printf("\t- position: %.2f, %.2f, %.2f\n", obj->cy.pos.x, obj->cy.pos.y, obj->cy.pos.z);
	printf("\t- direction: %.2f, %.2f, %.2f\n",
		obj->cy.dir.x, obj->cy.dir.y, obj->cy.dir.z);
	printf("\t- scale: %.2f\n", obj->cy.scale);
	printf("\t- half_height: %.2f\n", obj->cy.half_height);
	printf("\t- color: %.2f, %.2f, %.2f\n",
		obj->color.x, obj->color.y, obj->color.z);
}


void	debug_print_co(t_object *obj)
{
	printf(PRINT_PURPLE"cone:\n"PRINT_DEFAULT);
	printf("\t- position: %.2f, %.2f, %.2f\n", obj->co.pos.x, obj->co.pos.y, obj->co.pos.z);
	printf("\t- direction: %.2f, %.2f, %.2f\n",
		obj->co.dir.x, obj->co.dir.y, obj->co.dir.z);
	printf("\t- height: %.2f\n", obj->co.height);
	printf("\t- color: %.2f, %.2f, %.2f\n",
		obj->color.x, obj->color.y, obj->color.z);
}

void	debug_print_pl(t_object *obj)
{
	printf(PRINT_PURPLE"plane:\n"PRINT_DEFAULT);
	printf("\t- position: %.2f, %.2f, %.2f\n", obj->pl.pos.x, obj->pl.pos.y, obj->pl.pos.z);
	printf("\t- direction: %.2f, %.2f, %.2f\n",
		obj->pl.dir.x, obj->pl.dir.y, obj->pl.dir.z);
	printf("\t- color: %.2f, %.2f, %.2f\n",
		obj->color.x, obj->color.y, obj->color.z);
}

void	debug_print_sp(t_object *obj)
{
	printf(PRINT_PURPLE"sphere:\n"PRINT_DEFAULT);
	printf("\t- position: %.2f, %.2f, %.2f\n", obj->sp.pos.x, obj->sp.pos.y, obj->sp.pos.z);
	printf("\t- scale: %.2f\n", obj->sp.scale);
	printf("\t- color: %.2f, %.2f, %.2f\n",
		obj->color.x, obj->color.y, obj->color.z);
}

void	debug_print_world(t_window *win)
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
