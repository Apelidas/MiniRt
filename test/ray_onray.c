
#include "test.h"

static int	util(t_ray *test, t_vec3d *on)
{
	if (!ray_vec3d(test, on))
	{
		destroy_ray(test);
		free(on);
		return (0);
	}
	destroy_ray(test);
	free(on);
	return (1);
}

int	test_onray(void)
{
	t_vec3d	*tmp;
	t_ray	*help;

	if (!util(create_dray(1, 0, 0, 0), create_vec3d(10, 0, 0)))
		return (0);
	if (!util(create_dray(1, 0, 0, 0), create_vec3d(1.2345, 0, 0)))
		return (0);
	if (util(create_dray(1, 0, 0, 0), create_vec3d(10, 1, 0)))
		return (0);
	if (!util(create_dray(1, 0, 0, 0), create_vec3d(0.0001, 0, 0)))
		return (0);
	if (util(create_dray(1, 0, 0, 0), create_vec3d(-1, 0, 0)))
		return (0);
	tmp = create_vec3d(1, 2, 3);
	help = create_vray(tmp, create_vec3d(1, 0, 0), 0);
	if (!util(help, create_vec3d(10, 2, 3)))
		return (0);
	tmp = create_vec3d(1, 2, 3);
	help = create_vray(tmp, create_vec3d(1, 0, 0), 0);
	if (util(help, create_vec3d(10, 2.2, 3)))
		return (0);
	tmp = create_vec3d(1, 2, 3);
	help = create_vray(vec3d_cpy(tmp), create_vec3d(1, 0, 0), 0);
	if (!util(help, tmp))
		return (0);
	return (1);
}
