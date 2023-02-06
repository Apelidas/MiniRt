#include "operations.h"

/*
checks if a ray and a plane have a point of intesrsection
*/
int	plane_ray_touch(t_ray *ray, t_plane	*plane)
{
	double	dot;
	t_vec3d	*help;

	vec3d_norm(ray->dir);
	vec3d_norm(plane->norm);
	dot = vec3d_dot(ray->dir, plane->norm);
	help = create_vec3d(plane->origin->x - ray->origin->x,
			plane->origin->y - ray->origin->y,
			plane->origin->z - ray->origin->z);
	if (cmp_d(dot, 0))
		return (0);
	dot = vec3d_angle(help, ray->dir);
	free(help);
	if (dot > 90)
		return (0);
	return (1);
}


t_vec3d	*plane_ray_inter(t_ray *ray, t_plane *plane)
{
	double	t;
	t_vec3d	*tmp;
	t_vec3d	*inter;


	if (!ray || !plane)
		return (NULL);
	if (!plane_ray_touch(ray, plane))
		return (NULL);
	inter = create_vec3d(0, 0, 0);
	if (!inter)
		return (NULL);
	tmp = vec3d_sub(ray->origin, plane->origin);
	t = vec3d_dot(tmp, plane->norm);
	t = t / vec3d_dot(ray->dir, plane->norm);
	free(tmp);
	if (t >= 0)
	{
		free(inter);
		return (NULL);
	}
	inter->x = ray->origin->x + t * ray->dir->x;
	inter->y = ray->origin->y + t * ray->dir->y;
	inter->z = ray->origin->z + t * ray->dir->z;
	return (inter);
}