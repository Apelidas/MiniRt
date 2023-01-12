#include "test.h"

static int	util(t_vec3d *a, t_vec3d *b, double tst)
{
	int	out;

	out = cmp_d(vec3d_angle(a, b), tst);
	free(a);
	free(b);
	return (out);
}

int	vec_angle(void)
{
	if (!util(create_vec3d(1, 0, 0), create_vec3d(0, 0, 1), 90))
		return (0);
	if (!util(create_vec3d(1, 1, 0), create_vec3d(0, 0, 1), 90))
		return (0);
	if (!util(create_vec3d(1, 0, 1), create_vec3d(1, 0, 0), 45))
		return (0);
	if (!util(create_vec3d(1, -1, 0), create_vec3d(0, 1, 1), 120))
		return (0);
	return (1);
}