
#include "test.h"

static int	util(t_vec3d *a, t_vec3d *b)
{
	if (!vec3d_equal(a, b))
	{
		free(a);
		free(b);
		return (0);
	}
	free(a);
	free(b);
		return (1);
}

int	vec_cpy(void)
{
	if (!util(create_vec3d(0, 0, 0), create_vec3d(0, 0, 0)))
		return (0);
	if (!util(create_vec3d(1, 1, 1), create_vec3d(1, 1, 1)))
		return (0);
	if (util(create_vec3d(1, 0, 0), create_vec3d(0, 0, 0)))
		return (0);
	if (util(create_vec3d(0.1234, 0, 0), create_vec3d(0, 0, 0)))
		return (0);
	return (1);
}