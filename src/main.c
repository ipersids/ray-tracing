#include "minirt.h"

int	main(int argc, char **argv)
{
	int		exit_code;
	t_info	rt;

	rt_init_info(&rt);
	exit_code = rt_validate_input(argc, argv, &rt);
	if (0 != exit_code)
		rt_destroy_exit(&rt, exit_code);
	exit_code = rt_init_canvas(&rt);
	if (0 != exit_code)
		rt_destroy_exit(&rt, exit_code);
	rt_destroy_exit(&rt, EXIT_SUCCESS);
}
