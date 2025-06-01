/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal_floats.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:34:04 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/01 12:28:37 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	equal(float a, float b)
{
	const float	epsilon = 0.00001;

	if (fabs(a - b) < epsilon)
		return (true);
	return (false);
}
