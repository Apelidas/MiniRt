
#include "operations.h"

t_vec3d	*create_vec3d(double x, double y, double z)
{
	t_vec3d	*out;

	out = malloc(sizeof(t_vec3d));
	if (!out)
		return (NULL);
	out->x = x;
	out->y = y;
	out->z = z;
	return (out);
}

/* 
	calculates the length of a Vector from the Point of Origin {0, 0, 0}
 */
double	vec3d_len(t_vec3d *vector)
{
	double	a;
	double	b;
	double	c;

	a = pow(vector->x, 2.0);
	b = pow(vector->y, 2.0);
	c = pow(vector->z, 2.0);
	a = sqrt(a + b + c);
	return (a);
}

/* 
		multiplies 2 Vectors with each other
 */
t_vec3d	*vec3d_scalar(t_vec3d *a, t_vec3d *b)
{
	t_vec3d	*out;

	out = create_vec3d(a->x * b->x, a->y * b->y, a->z * b->z);
	if (!out)
		return (error("MALLOC_ERROR SCALAR"));
	return (out);
}

/* 
		Calculates the orthogonal vector to the plane created by 2 vectors
 */
t_vec3d	*vec3d_cross(t_vec3d *a, t_vec3d *b)
{
	t_vec3d	*out;

	out = create_vec3d(0, 0, 0);
	if (!out)
		return (error("MALLOC_ERROR CROSS"));
	out->x = (a->y * b->z) - (a->z * b->y);
	out->y = (a->z * b->x) - (a->x * b->z);
	out->z = (a->x * b->y) - (a->y * b->x);
	return (out);
}

/* 
	norminalizes the Vector: meaning setting it length to 1
 */
void	vec3d_norm(t_vec3d *vec)
{
	double	len;

	if (!vec)
		return ;
	len = vec3d_len(vec);
	if (cmp_d(len, 1)|| cmp_d(len, 0))
		return ;
	vec->x = vec->x / len;
	vec->y = vec->z / len;
	vec->z = vec->z / len;
}
