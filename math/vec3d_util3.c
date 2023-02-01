#include "operations.h"

t_vec3d	*vec3d_plus(t_vec3d	*a, t_vec3d	*b) // unneccessary alocations will be ommited in these funcs. 
{
	t_vec3d	*res;

	res = malloc (sizeof(t_vec3d));
	if (!res)
		return (NULL);
	res->x = a->x + b->x;
	res->y = a->y + b->y;
	res->z = a->z + b->z;
	return (res);
}

t_vec3d	*vec3d_mult_num(t_vec3d	*a, double b)
{
	t_vec3d	*res;

	res = malloc(sizeof(t_vec3d));
	if (!res)
		return (NULL);
	res->x = a->x * b;
	res->y = a->y * b;
	res->z = a->z * b;
	return (res);
}

t_vec3d	*vec3d_minus(t_vec3d *a, t_vec3d *b)
{
	t_vec3d	*res;

	res = malloc(sizeof(t_vec3d));
	if (!res)
		return (NULL);
	res->x = a->x - b->x;
	res->y = a->y - b->y;
	res->z = a->z - b->z;
	return (res);
}
