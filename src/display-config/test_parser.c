/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 00:51:58 by ipersids          #+#    #+#             */
/*   Updated: 2025/06/08 02:19:41 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
    char *valid_file[] = {"", "scene/shadow.rt"};
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

    // Array of pointers to all invalid scenes
    char **invalid_scenes[] = {
        invalid_scene_1,
        invalid_scene_2,
        invalid_scene_3,
        invalid_scene_4,
        NULL
    };

    for (int i = 0; invalid_scenes[i] != NULL; ++i) {
        exit_code = rt_parse_scene(&rt, invalid_scenes[i]);
        assert(exit_code != 0);
		// rt_perror(exit_code);
        free_and_init(&rt);
    }
}
