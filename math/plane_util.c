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

/*
returns the point of intersection of a plane and a ray.
returns NULL if there is none
*/
// t_vec3d *plane_ray_inter(t_ray *ray, t_plane *plane)
// {
// 	double t;
// 	t_vec3d *oc;
// 	t_vec3d *intersect;

// 	oc = vec3d_sub(ray->origin, plane->origin);
// 	t = vec3d_dot(plane->norm, oc) / vec3d_dot(plane->norm, ray->dir);
// 	if (t < 0)
// 	{
// 		free(oc);
// 		return (NULL);
// 	}
// 	vec3d_mult(ray->dir, t);
// 	intersect = vec3d_add(ray->origin, ray->dir);
// 	free(oc);
// 	return (intersect);
// }


t_vec3d	*plane_ray_inter(t_ray *ray, t_plane *plane)
{
	double	t;
	t_vec3d	*inter;

	if (!ray || !plane)
		return (NULL);
	if (!plane_ray_touch(ray, plane))
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
