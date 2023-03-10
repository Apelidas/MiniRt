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
	(void)trgb;
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
	double	out;

	tmp = create_vec3d(point->x - plane->origin->x,
			point->y - plane->origin->y, point->z - plane->origin->z);
	out = vec3d_dot(tmp, plane->norm);
	free(tmp);
	if (!cmp_d(out, 0))
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

double	plane_intersection(t_ray *ray, t_plane	*plane)
{
	double	tmp;
	t_vec3d	*tmp2;
	double	inter;

	tmp = vec3d_dot(ray->dir, plane->norm);
	if (cmp_d(tmp, 0))
		return (-1);
	tmp2 = vec3d_minus(plane->origin, ray->origin);
	inter = vec3d_dot(tmp2, plane->norm) / tmp;
	free(tmp2);
	if (inter < 0)
		return (-1);
	return (inter);
}
