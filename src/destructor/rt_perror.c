/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 00:19:51 by ipersids          #+#    #+#             */
/*   Updated: 2025/04/25 14:02:58 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

/**
 * @brief Returns a custom error message based on the exit code.
 * 
 * @param exit_code The exit code indicating the type of error.
 * @return const char* The error message corresponding to the exit code.
 */
static const char	*get_error_message(int exit_code);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Handles error reporting and displays appropriate error messages.
 * 
 * This function is used to print error messages to the standard error output
 * based on the provided exit code. It supports system errors, MLX42 library
 * errors, and custom errors.
 * 
 * @param exit_code The error code indicating the type of error.
 */
void	rt_perror(int exit_code)
{
	ft_putstr_fd(PRINT_RED"Error: "PRINT_DEFAULT, STDERR_FILENO);
	if (ERR_SYSTEM == exit_code)
	{
		perror("System");
	}
	else if (ERR_MLX42 == exit_code)
	{
		ft_putstr_fd(mlx_strerror(mlx_errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd(get_error_message(exit_code), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
}

/* ------------------- Private Function Implementation --------------------- */

static const char	*get_error_message(int exit_code)
{
	static const char	list[ERR_MAX % ERR_MODULO][100] = {
		"Usage: ./miniRT [path/file"EXTENTION"]",
		"Wrong file extension or empty name: should be [path/file"EXTENTION"]",
		"Read file: Overflow occurs when memory is reallocated",
		"Wrong element in the scene file",
		"Wrong amount of elements in the scene file"
	};

	if (!(ERR_MLX42 < exit_code && ERR_MAX > exit_code))
		return ("Uknown error code.");
	return (list[exit_code % ERR_MODULO]);
}
