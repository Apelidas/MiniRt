#include "operations.h"

/*
checks if a ray and a plane have a point of intesrsection
*/
int	plane_ray_touch(t_ray *ray, t_plane	*plane)
{
	if (vec3d_dot(ray->dir, plane->norm) == 0)
		return (0); // either ray has no touching point or ray is completely inside the plane.
	return (1);
}

/*
returns the point of intersection of a plane and a ray.
returns NULL if there is none
*/
t_vec3d	*plane_ray_inter(t_ray *ray, t_plane *plane)
{
	double	t;
	t_vec3d	*intersection;

	intersection = malloc(sizeof(t_vec3d));
	if (!plane_ray_touch(ray, plane))
		return (error ("no intersecting point!"));
	else
		t = (vec3d_dot(plane->origin, plane->norm) - vec3d_dot(ray->origin, plane->norm)) / vec3d_dot(ray->dir, plane->norm);
	intersection->x = ray->origin->x + t * ray->dir->x;
	intersection->y = ray->origin->y + t * ray->dir->y;
	intersection->z = ray->origin->z + t * ray->dir->z;
	return (intersection);
}
