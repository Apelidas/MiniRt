#include "operations.h"

/**
 * @brief returns a reversed ray to the input ray
 * 
 * @param ray 
 * @return t_ray* 
 */
t_ray	*ray_rev(t_ray *ray)
{
	t_ray	*rev;

	rev = ray_cpy(ray);
	if (!rev)
		return (NULL);
	rev->dir->x *= -1;
	rev->dir->y *= -1;
	rev->dir->z *= -1;
	return (rev);
}
