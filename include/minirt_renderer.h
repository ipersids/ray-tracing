#ifndef MINIRT_RENDERER_H
# define MINIRT_RENDERER_H

/* --------------------------- Camera and renderer -------------------------- */
/// @dir src/renderer

void			rt_camera_render(t_info *rt);
void			rt_camera_init(t_camera *cam, t_canvas *win);
t_color			rt_color_at(t_info *rt, t_ray *ray);
void			rt_intersect_world(t_info *rt, t_ray *ray);

t_ray			rt_get_ray(t_camera *cam, int32_t x, int32_t y);
uint32_t		rt_convert_to_rgba(const t_color *color);

/* --------------------------- Shapes calculations -------------------------- */
/// @dir src/shapes

t_intersections	intersect_sphere(t_sphere sphere, t_ray ray);
t_ray			transform_ray(t_ray ray, t_matrix matrix);

//t_intersections	hit_sphere(t_point center, float radius, t_ray ray);
t_vec3			ray_hit(t_ray ray, float t);
t_vec3			normal_at(t_object *obj, t_point world_point);
t_vec3			sphere_normal_at(t_sphere *sp, t_point world_point);
t_vec3			reflect(t_vec3 in, t_vec3 normal);
t_intersection	*find_closest_intersection(t_intersection *ts, int n_ts);

#endif // MINIRT_RENDERER_H
