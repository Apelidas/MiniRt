
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

int	test_raycpy(void)
{
	t_ray	*a;
	t_ray	*b;

	a = create_dray(1, 2, 3, 0);
	b = ray_cpy(a);
	if (!util(a, b))
		return (0);
	a = create_dray(1, 2, 3, 0);
	b = ray_cpy(a);
	if (!util(a, b))
		return (0);
	a = create_vray(create_vec3d(1, 2, 3), create_vec3d(1, 2, 3), 0);
	b = ray_cpy(a);
	if (!util(a, b))
		return (0);
	return (1);
}
