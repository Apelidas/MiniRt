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
