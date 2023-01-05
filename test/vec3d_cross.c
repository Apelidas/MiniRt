
#include "test.h"

static t_vec3d	*vec_crossutil(t_vec3d *a, t_vec3d *b)
{
	t_vec3d	*test;

	test = vec3d_cross(a, b);
	free(a);
	free(b);
	return (test);
}

int	vec_cross(void)
{
	t_vec3d	*a;
	t_vec3d	*b;
	t_vec3d	*test;
	int		out;

	out = 1;
	a = create_vec3d(1, 1, 1);
	b = create_vec3d(1, 1, 1);
	test = vec_crossutil(a, b);
	if (!cmp_d(test->x, 0) || !cmp_d(test->y, 0) || !cmp_d(test->z, 0))
		out = 0;
	free(test);
	a = create_vec3d(0, 0, 1);
	b = create_vec3d(0, 1, 0);
	test = vec_crossutil(a, b);
	if (!cmp_d(test->x, -1) || !cmp_d(test->y, 0) || !cmp_d(test->z, 0))
		out = 0;
	free(test);
	a = create_vec3d(1, 2, 3);
	b = create_vec3d(3, 4, 5);
	test = vec_crossutil(a, b);
	if (!cmp_d(test->x, -2) || !cmp_d(test->y, 4) || !cmp_d(test->z, -2))
		out = 0;
	free(test);
	return (out);
}
