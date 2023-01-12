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

/*
checks if a vector is inside a plane
*/
int	plane_point(t_vec3d *point, t_plane	*plane)
{
	t_vec3d	*tmp;
	tmp = create_vec3d(point->x - plane->origin->x, point->y - plane->origin->y, point->z - plane->origin->z);
	if (!cmp_d(vec3d_dot(tmp, plane->norm), 0))
		return (0);
	return (1);
}

/*
checks if a ray is inside a plane
*/
int	plane_ray_in(t_ray	*ray, t_plane	*plane)
{
	if (plane_point(ray->origin, plane) == 0)
		return (0);
	if (!cmp_d(vec3d_dot(ray->dir, plane->norm), 0))
		return (0);
	return (1);
}
