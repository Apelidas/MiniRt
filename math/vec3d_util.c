
#include "operations.h"

t_vec3d	*vec3d_cpy(t_vec3d *in)
{
	t_vec3d *out;

	out = create_vec3d(in->x, in->y, in->z);
	return (out);
}

/* 
	Compares 2 Vectors and if they are identical within error of cmp_d
 */
int	vec3d_equal(t_vec3d *a, t_vec3d *b)
{
	if (!a || !b)
		return (-1);
	if (!cmp_d(a->x, b->x))
		return (0);
	if (!cmp_d(a->y, b->y))
		return (0);
	if (!cmp_d(a->z, b->z))
		return (0);
	return (1);
}

double	vec3d_dot(t_vec3d	*a, t_vec3d *b)
{
	double	res;

	res = a->x * b->x + a->y * b->y + a->z * b->z;
	return (res);
}
