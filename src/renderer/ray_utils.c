#include "minirt.h"

t_intersection	*find_closest_intersection(t_intersection *ts, int n_ts)
{
	int	i;

	if (n_ts <= 0)
		return (NULL);
	i = 0;
	while (i < n_ts)
	{
		if (ts[i].t > EPSILON)
			return (&ts[i]);
		++i;
	}
	return (NULL);
}

t_vec3	reflect(t_vec3 in, t_vec3 normal)
{
	t_vec3	result;
	t_vec3	scaled_norm;

	scaled_norm = multiplication(normal, 2 * dot_product(in, normal));
	result = subtraction(in, scaled_norm);
	return (result);
}
