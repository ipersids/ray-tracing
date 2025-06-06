/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reerikai <reerikai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:38:57 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/03 11:40:14 by reerikai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

/* ------------------- Private Function Implementation --------------------- */

// t_pat	stripe_pattern(t_color a, t_color b, t_pattype type)
// {
// 	t_pat	pattern;

// 	pattern.type = type;
// 	pattern.color_a = a;
// 	pattern.color_b = b;
// 	pattern.has_pattern = true;
// 	pattern.transform = matrix_identity();
// 	pattern.inv_transform = inverse(pattern.transform);
// 	return (pattern);
// }

t_color	stripe_pattern_at(t_pat *pattern, t_point point)
{
	if ((int)point.x % 2 == 0)
		return (pattern->color_a);
	else
		return (pattern->color_b);
}
