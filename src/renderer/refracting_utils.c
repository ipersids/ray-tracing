/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refracting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:25:16 by reerikai          #+#    #+#             */
/*   Updated: 2025/07/05 02:31:41 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	update_container(t_obj_container *container, t_object *object)
{
	int	index;

	index = 0;
	if (is_inside_container(container, object, &index))
		remove_from_container(container, index);
	else
		add_to_container(container, object);
}

bool	is_inside_container(t_obj_container *container,
			t_object *object, int *index)
{
	int	i;

	i = 0;
	while (i < container->obj_count)
	{
		if (container->objs[i] == object)
		{
			*index = i;
			return (true);
		}
		i++;
	}
	return (false);
}

void	remove_from_container(t_obj_container *container, int index)
{
	int	i;

	i = index;
	while (i < container->obj_count - 1)
	{
		container->objs[i] = container->objs[i + 1];
		i++;
	}
	if (container->obj_count > 0)
		container->obj_count--;
}

void	add_to_container(t_obj_container *container, t_object *obj)
{
	if (container->obj_count >= MAX_CONTAINERS)
		return ;
	container->objs[container->obj_count] = obj;
	container->obj_count++;
}

float	get_refractive_index(t_obj_container *container)
{
	int	i;

	i = container->obj_count - 1;
	if (i <= 0)
		return (1.0f);
	if (!container->objs[i]->material)
		return (1.0f);
	if (!container->objs[i])
		return (1.0f);
	else
		return (container->objs[i]->material->refractive);
}
