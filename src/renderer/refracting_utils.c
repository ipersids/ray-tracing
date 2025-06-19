#include "minirt.h"

void	update_container(t_obj_container *container, t_object *object)
{
	int index;

	if (is_inside_container(container, object, &index))
		remove_from_container(container, index);
	else
		add_to_container(container, object);
}

bool	is_inside_container(t_obj_container *container, t_object *object, int *index)
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

void remove_from_container(t_obj_container *container, int index)
{
	int i = index;
	while (i < container->obj_count - 1)
	{
		container->objs[i] = container->objs[i + 1];
		i++;
	}
	if (container->obj_count > 0)
		container->obj_count--;
}

void add_to_container(t_obj_container *container, t_object *obj)
{
	if (container->obj_count >= MAX_CONTAINERS)
		return ;
	container->objs[container->obj_count] = obj;
	container->obj_count++;
}

float	get_refractive_index(t_obj_container *container)
{
	if (container->obj_count <= 0)
		return (1.0f);
	if (!container->objs[container->obj_count - 1]->material)
		return (1.0f);
	if (!container->objs[container->obj_count -1])
		return (1.0f);
	else
		return (container->objs[container->obj_count - 1]->material->refractive);
}
