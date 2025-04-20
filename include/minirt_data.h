/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_data.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:35:35 by ipersids          #+#    #+#             */
/*   Updated: 2025/04/20 13:43:09 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_DATA_H
# define MINIRT_DATA_H

# define EXTENTION ".rt"

/**
 * @brief Colors palette
 */
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define PURPLE "\033[0;35m"
# define DEFAULT "\033[0m"

/**
 * @brief Error codes
 * 
 * - ERR_SYSTEM: callback strerror(errno);
 * - ERR_MLX42: callback mlx_strerror(mlx_errno);
 * 
 * Internal program errors:
 * - ERR_AGRC: The program received the wrong number of arguments.
 * - ERR_EXTENSION: The file has an incorrect extension.
 * 
 * - ERR_MAX - limiter for array of error messages.
 */
typedef enum s_error
{
	ERR_SYSTEM = 98,
	ERR_MLX42,
	ERR_ARGC,
	ERR_EXTENSION,
	ERR_OVERFLOW,
	ERR_MAX
}	t_error;

# define ERR_MODULO ERR_ARGC
# define CAPACITY 10

#endif // MINIRT_DATA_H