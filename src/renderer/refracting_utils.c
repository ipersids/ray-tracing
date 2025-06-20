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

// FIX THIS!!!!

// ==3992360==ERROR: AddressSanitizer: SEGV on unknown address (pc 0x0000004df73c bp 0x7ffc9eb00d10 sp 0x7ffc9eb00bb0 T0)
// ==3992360==The signal is caused by a READ memory access.
// ==3992360==Hint: this fault was caused by a dereference of a high value address (see register values below).  Disassemble the provided pc to learn which register was used.
//     #0 0x4df73c in get_refractive_index /home/reerikai/miniRT2/src/renderer/refracting_utils.c:54:50
//     #1 0x4de830 in prepare_refraction_calculations /home/reerikai/miniRT2/src/renderer/refracting.c:18:11
//     #2 0x4d9a33 in precompute_data /home/reerikai/miniRT2/src/renderer/color_at.c:50:2
//     #3 0x4d9a33 in rt_color_at /home/reerikai/miniRT2/src/renderer/color_at.c:21:6
//     #4 0x4d9103 in rt_camera_render /home/reerikai/miniRT2/src/renderer/camera.c:43:14
//     #5 0x4d60fb in rt_render_hook /home/reerikai/miniRT2/src/hook/hook_render_scene.c:56:3
//     #6 0x4ec115 in mlx_loop (/home/reerikai/miniRT2/miniRT_bonus+0x4ec115)
//     #7 0x4ccfea in init_hook /home/reerikai/miniRT2/src/constructor/init_window.c:95:2
//     #8 0x4ccfea in rt_init_window /home/reerikai/miniRT2/src/constructor/init_window.c:57:2
//     #9 0x4ea86b in main /home/reerikai/miniRT2/src/main.c:12:14
//     #10 0x7f3de0c29d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16
//     #11 0x7f3de0c29e3f in __libc_start_main csu/../csu/libc-start.c:392:3
//     #12 0x41f624 in _start (/home/reerikai/miniRT2/miniRT_bonus+0x41f624)

// AddressSanitizer can not provide additional info.
// SUMMARY: AddressSanitizer: SEGV /home/reerikai/miniRT2/src/renderer/refracting_utils.c:54:50 in get_refractive_index


float	get_refractive_index(t_obj_container *container)
{
	int	count;

	count = container->obj_count - 1;
	if (count <= 0)
		return (1.0f);
	if (!container->objs[count]->material)
	 	return (1.0f);
	if (!container->objs[count])
	 	return (1.0f);
	else
		return (container->objs[count]->material->refractive);
}
