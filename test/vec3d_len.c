#include "test.h"

static int	len_util(t_vec3d *test, double len)
{
	if (!cmp_d(vec3d_len(test), len))
	{
		free(test);
		return (0);
	}
	free(test);
	return (1);
}

int	vec_len(void)
{
	t_vec3d	*test;

	test = create_vec3d(1, 0, 0);
	if (!len_util(test, 1))
		return (0);
	test = create_vec3d(0, 1, 0);
	if (!len_util(test, 1))
		return (0);
	test = create_vec3d(0, 0, 1);
	if (!len_util(test, 1))
		return (0);
	test = create_vec3d(1, 2, 2);
	if (!len_util(test, 3))
		return (0);
	test = create_vec3d(0, 0, 0);
	if (!len_util(test, 0))
		return (0);
	if (len_util(create_vec3d(1, 0, 0), 2))
		return (0);
	return (1);
}
