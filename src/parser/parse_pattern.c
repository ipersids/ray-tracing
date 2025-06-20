#include "minirt.h"

/* --------------------- Private function prototypes ----------------------- */

static inline bool		is_valid_eol(char *line);
static t_pattype	get_pattern_type(char *line);

/* --------------------------- Public Functions ---------------------------- */

int	rt_parse_pattern(t_info *rt, char **start)
{
	t_pattype	p_type;

	p_type = get_pattern_type(*start);
	if (PATTERN_MAX == p_type)
		return (ERR_PATTERN);
	if (PATTERN_DEFAULT != p_type)
	{
		rt->objs[rt->n_objs].pattern = &rt->patterns[p_type];
		rt->objs[rt->n_objs].has_pattern = true;
	}
	while (ft_isalpha(**start) || '_' == (**start))
		++(*start);
	return (0);
}

/* ------------------- Private Function Implementation -------------------- */

static t_pattype	get_pattern_type(char *line)
{
	if (ft_strncmp(line, "default", 7) == 0 && is_valid_eol(&line[7]))
		return (PATTERN_DEFAULT);
	if (ft_strncmp(line, "stripe", 6) == 0 && is_valid_eol(&line[6]))
		return (PATTERN_STRIPE);
	if (ft_strncmp(line, "gradient", 8) == 0 && is_valid_eol(&line[8]))
		return (PATTERN_GRADIENT);
	if (ft_strncmp(line, "checker", 7) == 0 && is_valid_eol(&line[7]))
		return (PATTERN_CHECKER);
	return (PATTERN_MAX);
}

static inline bool	is_valid_eol(char *line)
{
	return (ft_isspace(*line) || '\0' == (*line) || '#' == (*line));
}
