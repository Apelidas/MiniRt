#include "operations.h"

/**
 * @brief 
 * calculates the distance between vectors
 * @param a 
 * @param b 
 * @return double 
 */
double	vec3d_dist(t_vec3d *a, t_vec3d *b)
{
	t_vec3d	*help;
	double	out;

	help = create_vec3d(a->x - b->x, a->y - b->y, a->z - b->z);
	out = vec3d_len(help);
	free(help);
	return (out);
}

/**
 * @brief 
 * checks if 2 vectors are convergent(if one includes the other)
 * @param a 
 * @param b 
 * @return int 
 */
int	vec3d_vec3d_equal(t_vec3d *a, t_vec3d *b)
{
	t_ray	*help;
	t_ray	*tmp;

	tmp = create_dray(a->x, a->y, a->z, 0);
	help = create_dray(b->x, b->y, b->z, 0);
	if (ray_equal(tmp, help))
	{
		destroy_ray(tmp);
		destroy_ray(help);
		return (1);
	}
	destroy_ray(tmp);
	destroy_ray(help);
	return (0);
}

t_vec3d	*vec3d_add(t_vec3d *a, t_vec3d *b)
{
	t_vec3d	*out;

	out = vec3d_cpy(a);
	out->x += b->x;
	out->y += b->y;
	out->z += b->z;
	return (out);
}
/**
 * @brief calculates a - b
 * 
 * @param a 
 * @param b 
 * @return t_vec3d* 
 */
t_vec3d	*vec3d_sub(t_vec3d *a, t_vec3d *b)
{
	t_vec3d	*out;

	out = vec3d_cpy(a);
	out->x -= b->x;
	out->y -= b->y;
	out->z -= b->z;
	return (out);
}
