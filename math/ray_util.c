
#include "operations.h"

int	on_ray(t_ray *ray, t_vec3d *point)
{
	double	a;
	double	b;
	double	c;

	if (!ray || !point)
		return (-1);
	a = (point->x - ray->origin->x) / ray->dir->x;
	b = (point->y - ray->origin->y) / ray->dir->y;
	c = (point->z - ray->origin->z) / ray->dir->z;
	if (!cmp_d(a, b) || cmp_d(a, c))
		return (0);
	return (1);
}