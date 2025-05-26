/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_at.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:38:57 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/25 19:42:48 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static t_intersection	*intersect_world(t_info *rt, t_ray *ray);

/// @test -->
static t_intersections	sphere_intersect(t_sphere *sp, t_ray *ray);
/// end @test <---

/* --------------------------- Public Functions ---------------------------- */

t_color	rt_color_at(t_info *rt, t_ray *ray)
{
	
}

/* ------------------- Private Function Implementation --------------------- */

static t_intersection	*intersect_world(t_info *rt, t_ray *ray)
{
	size_t			i;
	t_intersections	xs;

	i = 0;
	while (i < rt->n_objs)
	{
		if (ELEMENT_SPHERE == rt->objs[i].id)
			xs = sphere_intersect(&rt->objs[i].sp, ray);
		++i;
	}
}

/// @test -->
/* ------------------- TESTING Function Implementation --------------------- */

static t_intersections	sphere_intersect(t_sphere *sp, t_ray *ray)
{
	t_intersections	res;

	return (res);
}

/// end @test <---