
#include "test.h"

static int	util(t_ray *a, t_ray *b)
{
	if (!ray_equal(a, b))
	{
		destroy_ray(a);
		destroy_ray(b);
		return (0);
	}
	destroy_ray(a);
	destroy_ray(b);
	return (1);
}

int	test_rayequal(void)
{
	t_ray	*a;
	t_ray	*b;

	a = create_dray(1, 0, 0, 0);
	b = create_dray(1, 0, 0, 0);
	if (!util(a, b))
		return (0);
	a = create_dray(1.123, 2, 3, 0);
	b = create_dray(1.123, 2, 3, 0);
	if (!util(a, b))
		return (0);
	a = create_dray(1, 0, 0, 0);
	b = create_vray(create_vec3d(1, 0, 0), create_vec3d(1, 0, 0), 0);
	if (!util(a, b))
		return (0);
	a = create_dray(1, 0, 0, 0);
	b = create_vray(create_vec3d(1, 0, 0), create_vec3d(-1, 0, 0), 0);
	if (!util(a, b))
		return (0);
	a = create_dray(1, 0, 0, 0);
	b = create_vray(create_vec3d(-1, 0, 0), create_vec3d(1, 0, 0), 0);
	if (!util(a, b))
		return (0);
	a = create_dray(1, 0, 0, 0);
	b = create_vray(create_vec3d(0, 1, 0), create_vec3d(1, 0, 0), 0);
	if (util(a, b))
		return (0);
	a = create_dray(1, 0, 0, 0);
	b = create_vray(create_vec3d(0, 0, 0), create_vec3d(1, 1, 0), 0);
	if (!util(a, b))
		return (0);
	return (1);
}