#include "operations.h"

/*
checks if a ray and a plane have a point of intesrsection
*/
static int	touch(t_ray *ray, t_plane	*plane)
{
	if (vec3d_dot(ray->dir, plane->norm) == 0)
		return (0);
	return (1);
}

/*
returns the point of intersection of a plane and a ray.
returns NULL if there is none
*/
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
	t = vec3d_dot(plane->origin, plane->norm)
		- vec3d_dot(ray->origin, plane->norm);
	t = t / vec3d_dot(ray->dir, plane->norm);
	inter->x = ray->origin->x + t * ray->dir->x;
	inter->y = ray->origin->y + t * ray->dir->y;
	inter->z = ray->origin->z + t * ray->dir->z;
	return (inter);
}