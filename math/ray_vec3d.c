#include "operations.h"

static int	ray_vec3d_util(t_ray *ray, t_vec3d *point)
{
	if (cmp_d(ray->dir->x, 0))
	{
		if (!cmp_d(ray->origin->x, point->x))
			return (0);
	}
	else if (cmp_d(ray->origin->x, point->x))
		return (0);
	if (cmp_d(ray->dir->y, 0))
	{
		if (!cmp_d(ray->origin->y, point->y))
			return (0);
	}
	else if (cmp_d(ray->origin->y, point->y))
		return (0);
	if (cmp_d(ray->dir->z, 0))
	{
		if (!cmp_d(ray->origin->z, point->z))
			return (0);
	}
	else if (cmp_d(ray->origin->z, point->z))
		return (0);
	return (1);
}

static int	ray_vec3d_norm(t_ray *ray, double a, double b, double c)
{
	if (!cmp_d(ray->dir->x, 0) && !cmp_d(ray->dir->y, 0))
		if (!cmp_d(a, b))
			return (0);
	if (!cmp_d(ray->dir->x, 0) && !cmp_d(ray->dir->z, 0))
		if (!cmp_d(a, c))
			return (0);
	if (!cmp_d(ray->dir->y, 0) && !cmp_d(ray->dir->z, 0))
		if (!cmp_d(b, c))
			return (0);
	return (1);
}

/**
 * @brief calculates if a point is on the ray or not
 * 
 * @param ray 
 * @param point 
 * @return int 
 */
int	ray_vec3d(t_ray *ray, t_vec3d *point)
{
	t_vec3d	help;

	if (!ray || !point)
		return (-1);
	help.x = 0;
	help.y = 0;
	help.z = 0;
	if (!cmp_d(ray->dir->x, 0))
		help.x = (point->x - ray->origin->x) / ray->dir->x;
	else
		help.x = (point->x - ray->origin->x);
	if (!cmp_d(ray->dir->y, 0))
		help.y = (point->y - ray->origin->y) / ray->dir->y;
	else
		help.y = (point->y - ray->origin->y);
	if (!cmp_d(ray->dir->z, 0))
		help.z = (point->z - ray->origin->z) / ray->dir->z;
	else
		help.z = (point->z - ray->origin->z);
	if (help.x < 0 || help.y < 0 || help.z < 0)
		return (0);
	if (!ray_vec3d_norm(ray, help.x, help.y, help.z))
		return (0);
	return (ray_vec3d_util(ray, point));
}
