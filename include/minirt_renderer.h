#ifndef MINIRT_RENDERER_H
# define MINIRT_RENDERER_H

/* --------------------------- Camera and renderer -------------------------- */
/// @dir src/camera

/// @file src/renderer/camera.c

void		rt_camera_render(t_info *rt);

/// @file src/camera/ray.c

t_ray		rt_get_ray(t_camera *camera, int32_t x, int32_t y);
t_color		ray_color(t_ray ray);

/// @file src/renderer/color.c

uint32_t	rt_convert_to_rgba(const t_color *color);

/* --------------------------- Shapes calculations -------------------------- */
/// @dir src/shapes

//float	hit_sphere(t_point center, float radius, t_ray ray);
t_intersections	hit_sphere(t_point center, float radius, t_ray ray);
t_vec3	ray_hit(t_ray ray, float t);
float	find_closest_intersection(t_intersections hits);

#endif // MINIRT_RENDERER_H
