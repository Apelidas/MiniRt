#include "operations.h"

t_plane	*create_plane(t_vec3d *origin, t_vec3d *norm, int trgb)
{
	t_plane	*out;

	if (!origin || !norm)
		return (NULL);
	out = malloc(sizeof(t_plane));
	if (!out)
		return (NULL);
	out->origin = origin;
	out->norm = norm;
	out->trgb = trgb;
	return (out);
}

void	destroy_plane(t_plane *todel)
{
	if (!todel)
		return ;
	if (todel->norm)
		free(todel->norm);
	if (todel->origin)
		free(todel->origin);
	free(todel);
}

int	plane_point(t_vec3d *point, t_plane	*plane) //not sure if it is correct...
{
	if (!cmp_d(vec3d_dot((point - plane->origin), plane->norm), 0))
		return (0);
	return (1);
}

// as I understood there is no such thing as vector on a plane.
// not sure what is the diff btw dira and dirb in the plane definition. i considered
//dira as the normal.
int	plane_ray_in(t_ray	*ray, t_plane	*plane)
{
	if (point_on_plane(ray->origin, plane) == 0)
		return (0);
	if (!cmp_d(vec3d_dot(ray->dir, plane->norm), 0))
		return (0);
	return (1);
}

int	plane_ray_touch(t_ray *ray, t_plane	*plane)
{
	if (vec3d_dot(ray->dir, plane->norm) == 0)
		return (0); // either ray has no touching point or ray is completely inside the plane.
	return (1);
}

t_vec3d	*plane_ray_intersect(t_ray *ray, t_plane	*plane)
{
	double	t;
	t_vec3d	*intersection;

	intersection = malloc(sizeof(t_vec3d));
	if (!ray_touches_plane(ray, plane))
		error ("no intersecting point!");
	else
		t = (vec3d_dot(plane->origin, plane->norm) - vec3d_dot(ray->origin, plane->norm)) / vec3d_dot(ray->dir, plane->norm);
	intersection->x = ray->origin->x + t * ray->dir->x;
	intersection->y = ray->origin->y + t * ray->dir->y;
	intersection->z = ray->origin->z + t * ray->dir->z;
	return (intersection);
}
