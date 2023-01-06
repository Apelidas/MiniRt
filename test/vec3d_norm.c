
#include "test.h"

static int	util(t_vec3d *test, t_vec3d *cmp)
{
	vec3d_norm(test);
	if (!vec3d_equal(test, cmp))
	{
		free(test);
		free(cmp);
		return (0);
	}
	free(test);
	free(cmp);
	return (1);
}

int	vec_norm(void)
{
	if (!util(create_vec3d(1, 0, 0), create_vec3d(1, 0, 0)))
		return (0);
	if (util(create_vec3d(0, 1, 0), create_vec3d(1, 0, 0)))
		return (0);
	if (!util(create_vec3d(4, 4, 2), create_vec3d(0.6666666, 0.6666666, 0.3333333)))
		return (0);
	return (1);
}