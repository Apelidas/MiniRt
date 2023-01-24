
#include "test.h"

static int	util(t_vec3d *test, t_vec3d *cmp)
{
	int	help;

	help = vec3d_equal(test, cmp);
	if (help)
	{
		free(test);
		free(cmp);
		return (1);
	}
	if (test)
		free(test);
	if (cmp)
		free(cmp);
	return (0);
}

int	vec_equal(void)
{
	if (!util(create_vec3d(0, 0, 0), create_vec3d(0, 0, 0)))
		return (0);
	if (util(create_vec3d(0, 0, 0), create_vec3d(1, 0, 0)))
		return (0);
	if (!util(create_vec3d(1, 2, 3), create_vec3d(1, 2, 3)))
		return (0);
	if (!util(create_vec3d(1.234, 2.345, 3.456),
			create_vec3d(1.234, 2.345, 3.456)))
		return (0);
	if (!util(create_vec3d(-1.234, 2.345, 3.456),
			create_vec3d(-1.234, 2.345, 3.456)))
		return (0);
	if (!util(create_vec3d(-1.234, -2.345, -3.456),
			create_vec3d(-1.234, -2.345, -3.456)))
		return (0);
	if (util(create_vec3d(-1.234, 2.345, 3.456),
			create_vec3d(1.234, 2.345, 3.456)))
		return (0);
	if (util(create_vec3d(-1.234, -2.345, 3.456),
			create_vec3d(1.234, 2.345, 3.456)))
		return (0);
	return (1);
}
