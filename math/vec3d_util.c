
#include "operations.h"

t_vec3d	*vec3d_cpy(t_vec3d *in)
{
	t_vec3d	*out;

	out = create_vec3d(in->x, in->y, in->z);
	return (out);
}

/* 
	Compares 2 Vectors and if they are identical within error of cmp_d
 */
int	vec3d_equal(t_vec3d *a, t_vec3d *b)
{
	if (!a && !b)
		return (1);
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

/*
calculates the dot(scalar)product of 2 vecotrs
*/
double	vec3d_dot(t_vec3d	*a, t_vec3d *b)
{
	double	res;

	res = a->x * b->x + a->y * b->y + a->z * b->z;
	return (res);
}

/*
calculates the angle between 2 vectors 
returns -1 (value < 0) if error
*/
double	vec3d_angle(t_vec3d *a, t_vec3d *b)
{
	double	out;

	if (!a || !b)
		return (-1);
	if (!vec3d_len(a) || !vec3d_len(b))
		return (-1);
	out = (vec3d_dot(a, b)) / (vec3d_len(a) * vec3d_len(b));
	out = acos(out) * (180 / M_PI);
	return (out);
}

/**
 * @brief multiplies vector by mult
 * 
 * @param vec 
 * @param mult 
 */
void	vec3d_mult(t_vec3d *vec, double mult)
{
	vec->x *= mult;
	vec->y *= mult;
	vec->z *= mult;
}
