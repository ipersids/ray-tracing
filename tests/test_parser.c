/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 00:51:58 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/20 01:39:13 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_tests.h"

static void test_rt_parse_scene_invalid(void);

static void	free_and_init(t_info *rt)
{
	if (NULL != rt->objs)
		free(rt->objs);
	if (NULL != rt->lights)
		free(rt->lights);
	if (NULL != rt->ts)
		free(rt->ts);
	rt_init_info(rt);
}

void test_parser(void) {
	t_info rt;
    int exit_code;
    char *valid_file[] = {"", "tests/shadow.rt"};
    char *invalid_files[] = {
        "scene/badnameerror.rt",
        "badpatherror/subject.rt",
        "scene/subject.badextensionerror",
        "",
        ".rt",
        "    ",
        NULL
    };

    rt_init_info(&rt);

    printf(PRINT_PURPLE"\n\nTEST PARSING: \n"PRINT_DEFAULT);

    printf("TEST valid case: ");
    exit_code = rt_validate_input(2, valid_file, &rt);
    assert(exit_code == 0);
    free_and_init(&rt);
    printf(PRINT_GREEN"success\n"PRINT_DEFAULT);

    printf("TEST invalid amount of arguments: ");
    assert(rt_validate_input(-10, valid_file, &rt) == ERR_ARGC);
    assert(rt_validate_input(0, valid_file, &rt) == ERR_ARGC);
    assert(rt_validate_input(1, valid_file, &rt) == ERR_ARGC);
    assert(rt_validate_input(3, valid_file, &rt) == ERR_ARGC);
    assert(rt_validate_input(13, valid_file, &rt) == ERR_ARGC);
    printf(PRINT_GREEN"success\n"PRINT_DEFAULT);

    printf("TEST invalid filename: ");
    for (int i = 0; invalid_files[i] != NULL; ++i) {
        char *argv[] = {"", invalid_files[i]};
        exit_code = rt_validate_input(2, argv, &rt);
        assert(exit_code == ERR_EXTENSION || exit_code == ERR_SYSTEM);
        free_and_init(&rt);
    }
    printf(PRINT_GREEN"success\n"PRINT_DEFAULT);

	printf("TEST rt_parse_scene (invalid): ");
	test_rt_parse_scene_invalid();
	printf(PRINT_GREEN"success\n"PRINT_DEFAULT);
}

static void test_rt_parse_scene_invalid(void) {
    t_info rt;
    int exit_code;

	rt_init_info(&rt);
	 
	// Unknown object type
    char *invalid_scene_1[] = {
        "A 0.2 255,255,255",
        "C 0,0,0 0,0,1 70",
        "L 10,10,10 0.7 255,255,255",
        "xx 0,0,20 10 255,0,0",
        NULL
    };

	// Too many cameras
    char *invalid_scene_2[] = {
        "A 0.2 255,255,255",
        "C 0,0,0 0,0,1 70",
        "C 1,1,1 0,0,1 70",
        "L 10,10,10 0.7 255,255,255",
        NULL
    };

	// Too many ambients
    char *invalid_scene_3[] = {
        "A 0.2 255,255,255",
        "A 0.1 100,100,100",
        "C 0,0,0 0,0,1 70",
        "L 10,10,10 0.7 255,255,255",
        NULL
    };

    char *invalid_scene_4[] = {
        NULL
    };

	// Invalid FOV (too high)
    char *invalid_scene_5[] = {
        "A 0.2 255,255,255",
        "C 0,0,0 0,0,1 200",
        "L 10,10,10 0.7 255,255,255",
        NULL
    };

	// Plane with zero direction vector
    char *invalid_scene_6[] = {
        "A 0.2 255,255,255",
        "C 0,0,0 0,0,1 70",
        "L 10,10,10 0.7 255,255,255",
        "pl 0,10,0 0,0,0 255,255,255",
        NULL
    };

	// Invalid color value (out of range)
    char *invalid_scene_7[] = {
        "A 0.2 255,255,255",
        "C 0,0,0 0,0,1 70",
        "L 10,10,10 0.7 255,255,255",
        "sp 0,0,20 10 300,0,0",
        NULL
    };

	// Camera forward parallel to world up (gimbal lock)
    char *invalid_scene_8[] = {
    	" A 0.3 255,255,255",
		"C 0,-1,-150 0,1,0 40",
		"L -25,45,-30 0.8 255,255,255",
        NULL
    };

	// Camera pitch exceeds +60 degrees
	// normalized y component > sin(60°)
    char *invalid_scene_9[] = {
        "A 0.2 255,255,255",
        "C 0,0,0 0,0.89,0.1 70",
        "L 10,10,10 0.7 255,255,255",
        NULL
    };

	// Sphere with negative radius
    char *invalid_scene_10[] = {
        "A 0.2 255,255,255",
        "C 0,0,0 0,0,1 70",
        "L 10,10,10 0.7 255,255,255",
        "sp 0,0,20 -5 255,0,0",
        NULL
    };

    // Array of pointers to all invalid scenes
    char **invalid_scenes[] = {
        invalid_scene_1,
        invalid_scene_2,
        invalid_scene_3,
        invalid_scene_4,
        invalid_scene_5,
        invalid_scene_6,
        invalid_scene_7,
        invalid_scene_8,
        invalid_scene_9,
		invalid_scene_10,
        NULL
    };

    for (int i = 0; invalid_scenes[i] != NULL; ++i) {
        exit_code = rt_parse_scene(&rt, invalid_scenes[i]);
		printf("[%d] exit_code = %d\n", i, exit_code);
        assert(exit_code != 0);
		// rt_perror(exit_code);
        free_and_init(&rt);
    }
}
