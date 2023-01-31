#include "operations.h"

t_vec3d	*cyl_plane_ray(t_ray *ray, t_plane *plane)
{
	double	t;
	t_vec3d	*inter;

	if (!ray || !plane)
		return (NULL);
	inter = create_vec3d(0, 0, 0);
	if (!inter)
		return (NULL);
	t = vec3d_dot(plane->origin, plane->norm)
		- vec3d_dot(ray->origin, plane->norm);
	t = t / vec3d_dot(ray->dir, plane->norm);
	inter->x = ray->origin->x + t * ray->dir->x;
	inter->y = ray->origin->y + t * ray->dir->y;
	inter->z = ray->origin->z + t * ray->dir->z;
	return (inter);
}