/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_elements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:53:41 by ipersids          #+#    #+#             */
/*   Updated: 2025/04/29 19:04:03 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_light_default(t_light *light);

int	ft_init_elements(t_counter cnt, t_info *rt)
{
	bool	is_default;

	is_default = false;
	rt->objs = malloc(cnt.figures * sizeof(t_object));
	if (!rt->objs)
		return (ERR_SYSTEM);
	if (0 == cnt.lights)
	{
		is_default = true;
		cnt.lights += 1;
		rt->n_lights = 1;
	}
	rt->lights = malloc(cnt.lights * sizeof(t_object));
	if (!rt->lights)
		return (ERR_SYSTEM);
	if (is_default)
		init_light_default(rt->lights);
}

void	init_light_default(t_light *light)
{
	light->pos.x = DEFAULT_LIGHT_POSITION_X;
	light->pos.y = DEFAULT_LIGHT_POSITION_Y;
	light->pos.z = DEFAULT_LIGHT_POSITION_Z;
	light->bright = DEFAULT_LIGHT_BRIGHTNESS;
}
