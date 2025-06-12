/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:47:12 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/12 17:41:55 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

/**
 * @brief Initialize default camera settings.
 * @param camera Pointer to the camera structure.
 */
static void	init_camera(t_camera *camera);

/**
 * @brief Initializes the window with the necessary properties.
 * @param window A pointer to the `t_window` structure to be initialized.
 */
static void	init_window(t_window *window);


static void	init_material(t_material *materials);
static void	init_pattern(t_pat *patterns);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Initialize the ray tracing information structure.
 * @param rt Pointer to the ray tracing information structure.
 */
void	rt_init_info(t_info *rt)
{
	const t_color	color = (t_color){1.0f, 1.0f, 1.0f};
	const float		ratio = 0.1f;

	ft_memset(rt, 0, sizeof(t_info));
	rt->amb_intensity = multiplication(color, ratio);
	init_camera(&rt->camera);
	init_window(&rt->win);
	init_material(rt->materials);
	init_pattern(rt->patterns);
}

/* ------------------- Private Function Implementation --------------------- */

static void	init_camera(t_camera *cam)
{
	cam->forward = (t_vec3){0.0f, 0.0f, 1.0f};
	cam->pos = (t_point){0.0f, 0.0f, -100.0f};
	cam->fov = 40.0f;
}

static void	init_window(t_window *window)
{
	window->height = HEIGHT_DEFAULT;
	window->width = WIDTH_DEFAULT;
	window->world_up = (t_vec3){0.0f, 1.0f, 0.0f};
	window->rendered = false;
	window->resized = false;
}

static void	init_material(t_material *materials)
{
	materials[MATERIAL_DEFAULT] = init_default_material();
	materials[MATERIAL_LAMBERTIAN] = init_lambertian_material();
	materials[MATERIAL_METALL] = init_metal_material();
	materials[MATERIAL_RUSTED_METALL] = init_rasted_metal_material();
	materials[MATERIAL_GLASS] = init_glass_material();
	materials[MATERIAL_DIAMOND] = init_diamond_material();
	materials[MATERIAL_PLASTIC] = init_plastic_material();
	materials[MATERIAL_CERAMIC] = init_ceramic_material();
	materials[MATERIAL_MIRROR] = init_mirror_material();
	materials[MATERIAL_WATER] = init_water_material();
	materials[MATERIAL_ICE] = init_ice_material();
}

static void	init_pattern(t_pat *patterns)
{
	patterns[PATTERN_STRIPE] = set_stripe_pattern();
	patterns[PATTERN_GRADIENT] = set_gradient_pattern();
	patterns[PATTERN_CHECKER] = set_checker_pattern();
	// patterns[PATTERN_RADIANT_GRADIENT] = init_glass_pattern();
	// patterns[PATTERN_RING] = init_lambertian_pattern();
}
