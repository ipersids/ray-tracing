#ifndef MINIRT_RENDERER_H
# define MINIRT_RENDERER_H

/* --------------------------- Camera and renderer -------------------------- */
/// @dir src/renderer

void			rt_camera_render(t_info *rt);
void			rt_camera_init(t_camera *cam, t_window *win);
void			rt_reset_camera(t_info *rt);
void			rt_save_camera_settings(t_camera *camera);
t_color			rt_color_at(t_info *rt, t_ray *ray, int ray_bounces);
t_vec3			rt_normal_at(t_object *obj, t_point world_point, t_type otype);
void			rt_intersect_world(t_info *rt, t_ray *ray);
t_intersection	*find_closest_intersection(t_intersection *ts, int n_ts);

t_ray			rt_get_ray(t_camera *cam, int32_t x, int32_t y);
t_vec3			ray_hit(t_ray ray, float t);
t_ray			transform_ray(t_ray ray, t_matrix matrix);


/* --------------------------- Sphere calculations -------------------------- */

t_intersections	intersect_sphere(t_sphere sphere, t_ray ray);
t_vec3			sphere_normal_at(t_sphere *sp, t_point world_point);
t_vec3			reflect(t_vec3 in, t_vec3 normal);

/* --------------------------- Plane calculations -------------------------- */

t_intersections	rt_intersect_plane(const t_plane *pl, t_ray ray);
t_vec3			rt_plane_normal_at(const t_plane *pl);

/* ------------------------- Cylinder calculations ------------------------- */

t_intersections	rt_intersect_cylinder(const t_cylinder *cy, t_ray ray);
t_vec3			rt_cylinder_normal_at(const t_cylinder *cy, t_point w_point);
t_intersections	rt_intersect_cylinder_cap(const t_cylinder *cy, t_ray ray);
t_vec3			rt_cap_normal_at(const t_cylinder *cy, t_point w_point);

/* --------------------------- Cone calculations --------------------------- */

t_intersections	rt_intersect_cone(const t_cone *co, t_ray r);
t_vec3			rt_cone_normal_at(const t_cone *co, t_point w_point);
t_intersections	rt_intersect_cone_cap(const t_cone *co, t_ray ray);
t_vec3			rt_cone_cap_normal_at(const t_cone *co, t_point w_point);

/* ----------------- Refraction and reflection calculations ----------------- */

void			set_dark(t_phong_color *pc);
void			set_color(t_phong_color *pc, t_material *m, t_phong_vars *vars, t_light light);
void			prepare_refraction_calculations(t_info *rt, t_intersection *target, float *n1, float *n2);
void			update_container(t_obj_container *container, t_object *object);
void 			remove_from_container(t_obj_container *container, int index);
void 			add_to_container(t_obj_container *container, t_object *obj);

bool			light_behind_surface(float l_dot_norm);
bool			in_shadow(t_info *rt, t_point point);
bool			is_inside_container(t_obj_container *container, t_object *object, int *index);

float			get_refractive_index(t_obj_container *container);
float			schlick(t_phong_vars vars);

t_color			reflected_color(t_info *rt, t_phong_vars vars, int ray_bounces);
t_color			refracted_color(t_info *rt, t_phong_vars vars, int remaining);

#endif // MINIRT_RENDERER_H
