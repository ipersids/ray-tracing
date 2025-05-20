/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_submatrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 00:32:24 by ipersids          #+#    #+#             */
/*   Updated: 2025/05/20 15:42:07 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

inline static bool			is_removed(size_t *src_n, size_t rm_n);
inline static t_subm_var		init_variables(void);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Returns a submatrix with the specified row and column removed.
 * 
 * Removes the row `rm_row` and column `rm_col` from matrix `m` 
 * and returns the resulting submatrix.
 * 
 * @param m The original matrix.
 * @param rm_row The row to remove.
 * @param rm_col The column to remove.
 * @return t_matrix The resulting submatrix.
 */
t_matrix	submatrix(t_matrix m, size_t rm_row, size_t rm_col)
{
	t_subm_var	var;

	var = init_variables();
	while (m.dimension > var.src_row)
	{
		if (is_removed(&var.src_row, rm_row))
			continue ;
		var.src_col = 0;
		var.col = 0;
		while (m.dimension > var.src_col)
		{
			if (is_removed(&var.src_col, rm_col))
				continue ;
			var.res.data[var.row][var.col] = m.data[var.src_row][var.src_col];
			++var.col;
			++var.src_col;
		}
		++var.row;
		++var.src_row;
	}
	var.res.dimension = m.dimension - 1;
	return (var.res);
}

/* ------------------- Private Function Implementation --------------------- */

inline static t_subm_var	init_variables(void)
{
	t_subm_var	res;

	res.res = matrix_empty();
	res.col = 0;
	res.row = 0;
	res.src_col = 0;
	res.src_row = 0;
	return (res);
}

inline static bool	is_removed(size_t *src_n, size_t rm_n)
{
	if (*src_n == rm_n)
	{
		*src_n += 1;
		return (true);
	}
	return (false);
}
