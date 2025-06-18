#ifndef MINIRT_RENDERER_H
# define MINIRT_RENDERER_H

/* --------------------------- Camera and renderer -------------------------- */
/// @dir src/renderer

void			rt_camera_render(t_info *rt);
void			rt_camera_init(t_camera *cam, t_window *win);
void			rt_reset_camera(t_info *rt);
void			rt_save_camera_settings(t_camera *camera);
t_color			rt_color_at(t_info *rt, t_ray *ray, int ray_bounces);
t_vec3			rt_normal_at(t_info *rt, t_object *obj, t_point p, t_type id);
void			rt_intersect_world(t_info *rt, t_ray *ray);
t_intersection	*find_closest_intersection(t_intersection *ts, int n_ts);

t_ray			rt_get_ray(t_camera *cam, int32_t x, int32_t y);
t_vec3			ray_hit(t_ray ray, float t);
t_ray			transform_ray(t_ray ray, t_matrix matrix);
t_vec3			reflect(t_vec3 in, t_vec3 normal);

/* --------------------------- Sphere calculations -------------------------- */

t_intersections	intersect_sphere(t_sphere sphere, t_ray ray);
t_vec3			sphere_normal_at(t_sphere *sp, t_point world_point);
t_vec3			rt_sphere_bumped_normal_at(mlx_image_t *tex, t_sphere *sp,
					t_point *p);

/* --------------------------- Plane calculations -------------------------- */

t_intersections	rt_intersect_plane(const t_plane *pl, t_ray ray);
t_vec3			rt_plane_normal_at(const t_plane *pl);
t_vec3			rt_plane_bumped_normal_at(mlx_image_t *tex, t_plane *pl,
					t_point *p);

/* ------------------------- Cylinder calculations ------------------------- */

t_intersections	rt_intersect_cylinder(const t_cylinder *cy, t_ray ray);
t_vec3			rt_cylinder_normal_at(const t_cylinder *cy, t_point w_point);
t_vec3			rt_cylinder_bumped_normal_at(mlx_image_t *tex, t_cylinder *cy,
					t_point *p);
t_intersections	rt_intersect_cylinder_cap(const t_cylinder *cy, t_ray ray);
t_vec3			rt_cylinder_cap_normal_at(const t_cylinder *cy, t_point point);
t_vec3			rt_cap_bumped_normal_at(mlx_image_t *tex, t_cylinder *cy,
					t_point *p);

/* --------------------------- Cone calculations --------------------------- */

t_intersections	rt_intersect_cone(const t_cone *co, t_ray r);
t_vec3			rt_cone_normal_at(const t_cone *co, t_point w_point);
t_vec3			rt_cone_bumped_normal_at(mlx_image_t *tex, t_cone *co,
					t_point *p);
t_intersections	rt_intersect_cone_cap(const t_cone *co, t_ray ray);
t_vec3			rt_cone_cap_normal_at(const t_cone *co, t_point w_point);
t_vec3			rt_cone_cap_bumped_normal_at(mlx_image_t *tex, t_cone *co,
					t_point *p);

#endif // MINIRT_RENDERER_H
