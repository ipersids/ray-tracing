#ifndef MINIRT_RENDERER_H
# define MINIRT_RENDERER_H

/* --------------------------- Camera and renderer -------------------------- */
/// @dir src/camera

/// @file src/renderer/camera.c

void		rt_camera_render(t_info *rt);

/// @file src/camera/ray.c

t_ray		rt_get_ray(t_camera *camera, int32_t x, int32_t y);
t_color		ray_color(t_ray ray, t_sphere sphere);

/// @file src/renderer/color.c

uint32_t	rt_convert_to_rgba(const t_color *color);

/* --------------------------- Shapes calculations -------------------------- */
/// @dir src/shapes

t_intersections	intersect_sphere(t_sphere sphere, t_ray ray);
t_ray	transform_ray(t_ray ray, t_matrix matrix);

t_sphere	init_sphere(void);

//t_intersections	hit_sphere(t_point center, float radius, t_ray ray);
t_vec3	ray_hit(t_ray ray, float t);
t_vec3	normal_at(t_sphere sphere, t_point world_point);
t_vec3	reflect(t_vec3 in, t_vec3 normal);
float	find_closest_intersection(t_intersections hits);

#endif // MINIRT_RENDERER_H
