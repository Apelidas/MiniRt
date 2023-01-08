#include "operations.h"

int	point_on_plane(t_vec3d *point, t_plain	*plane) //not sure if it is correct...
{
	if (vec3d_cross((point - plane->origin), plane->dir_a) != 0)
		return (0);
	return (1);
}

// as I understoof there is no such thing as vector on a plane.
// not sure what is the diff btw dira and dirb in the plane definition. i considered
//dira as the normal.

int	ray_on_plane(t_ray	*ray, t_plain	*plane)
{
	if (point_on_plane(ray->origin, plane) == 0)
		return (0);
	if (vec3d_cross(ray->dir, plane->dir_a) != 0)
		return (0);
	return (1);
}

int	ray_touches_plane(t_ray *ray, t_plain	*plane)
{
	if (dot_product(ray->dir, plane->dir_a) == 0)
		return (0); // either ray has no touching point or ray is completely inside the plane.
	return (1);
}

t_vec3d	*intersecting_point_ray_plane(t_ray *ray, t_plain	*plane)
{
	double	t;
	t_vec3d	*intersection;

	intersection = malloc(sizeof(t_vec3d));
	if (!ray_touches_plane(ray, plane))
		error ("no intersecting point!");
	else
		t = (dot_product(plane->origin, plane->dir_a) - dot_product(ray->origin, plane->dir_a)) / dot_product(ray->dir, plane->dir_a);
	intersection->x = ray->origin->x + t * ray->dir->x;
	intersection->y = ray->origin->y + t * ray->dir->y;
	intersection->z = ray->origin->z + t * ray->dir->z;
	return (intersection);
}
