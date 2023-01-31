#include "operations.h"

static int	touch(t_ray *ray, t_plane	*plane)
{
	double	dot;

	dot = vec3d_dot(ray->dir, plane->norm);
	if (cmp_d(dot, 0))
		return (0);
	return (1);
}

t_vec3d	*cyl_plane_ray(t_ray *ray, t_plane *plane)
{
	double	t;
	t_vec3d	*inter;

	if (!ray || !plane)
		return (NULL);
	if (!touch(ray, plane))
		return (NULL);
	inter = create_vec3d(0, 0, 0);
	if (!inter)
		return (NULL);
	print_vec3d(ray->dir);
	t = vec3d_dot(plane->origin, plane->norm)
		- vec3d_dot(ray->origin, plane->norm);
	t = t / vec3d_dot(ray->dir, plane->norm);
	inter->x = ray->origin->x + t * ray->dir->x;
	inter->y = ray->origin->y + t * ray->dir->y;
	inter->z = ray->origin->z + t * ray->dir->z;
	print_vec3d(inter);
	return (inter);
}