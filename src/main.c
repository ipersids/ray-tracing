#include "minirt.h"

// static void	run_unit_tests(void)
// {
// 	printf(PRINT_GREEN"RUNNING UNIT TESTS:"PRINT_DEFAULT);
// 	test_matrix_math();
// 	test_matrix_transformation();
// 	printf("\n\n");
// }

// int	main(int argc, char **argv)
// {
// 	int		exit_code;
// 	t_info	rt;

// 	run_unit_tests(); /// @note delete
// 	rt_init_info(&rt);
// 	exit_code = rt_validate_input(argc, argv, &rt);
// 	if (0 != exit_code)
// 		rt_destroy_exit(&rt, exit_code);
// 	ft_printf("File: %s\n", argv[1]); /// @note delete
// 	debug_print_info(&rt); /// @note delete
// 	exit_code = rt_init_canvas(&rt);
// 	if (0 != exit_code)
// 		rt_destroy_exit(&rt, exit_code);
// 	rt_destroy_exit(&rt, EXIT_SUCCESS);
// 	return (exit_code);
// }

t_vec3	reflect(t_vec3 in, t_vec3 normal)
{
	t_vec3	result;
	t_vec3	scaled_norm;

	scaled_norm = multiplication(normal, 2 * dot_product(in, normal));
	result = subtraction(in, scaled_norm);
	return (result);
}

void	print_vector(char *msg, t_vec3 vec)
{
	printf("%s x = %.2f y = %.2f z = %.2f\n", msg, vec.x, vec.y, vec.z);
}

// int	main(int argc, char **argv)
// {
// 	int		exit_code;
// 	t_info	rt;

// 	run_unit_tests(); /// @note delete
// 	rt_init_info(&rt);
// 	exit_code = rt_validate_input(argc, argv, &rt);
// 	if (0 != exit_code)
// 		rt_destroy_exit(&rt, exit_code);
// 	ft_printf("File: %s\n", argv[1]); /// @note delete
// 	debug_print_info(&rt); /// @note delete
// 	t_matrix	translation = matrix_translation(0, 1, 0);
// 	rt.objs[0].sp.transform = translation;
// 	t_vec3 n = normal_at(rt.objs[0].sp, (t_point){0, 1.70711, -0.70711});
// 	print_vector("Normal at vector: ", n);
// 	t_vec3	reflection = reflect((t_vec3){0, -1, 0}, (t_vec3){sqrt(2) / 2, sqrt(2) / 2, 0});
// 	print_vector("Reflect ", reflection);
// 	return (0);
// }

t_plight	point_light(t_color intensity, t_point position)
{
	t_plight	result;

	result.intensity = intensity;
	result.position = position;
	return (result);
}

t_material	default_material(void)
{
	t_material	result;

	result.color = (t_color){1, 1, 1};
	result.ambient = 0.1;
	result.diffuse = 0.9;
	result.specular = 0.9;
	result.shininess = 200.0;
	return (result);
}

void	set_material(t_sphere sphere, t_material material)
{
	sphere.material = material;
}

t_color	lighting(t_material m, t_point pos, t_plight light, t_vec3 eyev, t_vec3 normalv)
{
	t_color	effective_color;
	t_color	ambient;
	t_color	diffuse;
	t_color	specular;
	t_color	result;
	t_vec3	lightv;
	t_vec3	reflectv;
	float	light_dot_normal;
	float	reflect_dot_eye;
	float	factor;

	effective_color = multiply_colors(m.color, light.intensity);
	lightv = normalize(subtraction(light.position, pos));
	ambient	= multiplication(effective_color, m.ambient);
	light_dot_normal = dot_product(lightv, normalv);

	if (light_dot_normal < 0)
	{
		diffuse = (t_color){0, 0, 0};
		specular = (t_color){0, 0, 0};
	}
	else
	{
		diffuse = multiplication(effective_color, m.diffuse * light_dot_normal);
		reflectv = reflect(negation(lightv), normalv);
		reflect_dot_eye = dot_product(reflectv, eyev);
		if (reflect_dot_eye <= 0)
			specular = (t_color){0, 0, 0};
		else
		{
			factor = powf(reflect_dot_eye, m.shininess);
			specular = multiplication(light.intensity, m.specular * factor);
		}
	}
	result = addition(addition(ambient, diffuse), specular);
	print_vector("Material color:", m.color);
	printf("Material ambient: %.2f\n", m.ambient);
	printf("Material diffuse: %.2f\n", m.diffuse);
	printf("Material specular: %.2f\n", m.specular);
	printf("Material shininess: %.2f\n", m.shininess);
	print_vector("Light intensity:", light.intensity);
	print_vector("Effective color:", effective_color);
	print_vector("Ambient color:", ambient);
	print_vector("Diffuse color:", diffuse);
	print_vector("Specular color:", specular);
	print_vector("Result color:", result);
	print_vector("Lightv:", lightv);
	//print_vector("Reflectv:", reflectv);
	return (result);
}

int main(void) {
	t_material m = default_material();
	t_point position = (t_point){0, 0, 0};

	t_vec3 eyev = (t_vec3){0, 0, -1};
	t_vec3 normalv = (t_vec3){0, 0, -1};
	t_plight light = point_light((t_point){0, 0, -10}, (t_color){1, 1, 1});
	t_color result = lighting(m, position, light, eyev, normalv);

	printf("Color: %.2f, %.2f, %.2f\n", result.x, result.y, result.z);  // Expected 1.9, 1.9, 1.9
}
