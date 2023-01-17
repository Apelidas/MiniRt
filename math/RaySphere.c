#include "operations.h"

int	sphere_ray_touch(t_ray *ray, t_sphere *ball)
{
	double	dist;

	if (!ray || !ball)
		return (-1);
	dist = ray_vec3d_dist(ray, ball->origin);
	if (dist < 0)
		return (-1);
	if (dist >= 0 && dist <= ball->d / 2)
		return (1);
	return (0);
}

static t_vec3d	*closest_point(t_ray *ray, t_vec3d *point, double dist)
{
	t_vec3d	*out;
	t_vec3d	*tmp;
	t_vec3d	*help;

	tmp = create_vec3d(point->x - ray->origin->x, point->y - ray->origin->y, point->z - ray->origin->z);
	help = vec3d_cross(tmp, ray->dir);
	vec3d_norm(help);
	vec3d_mult(help, dist);
	out = create_vec3d(point->x + help->x, point->y + help->y, point->z + help->z);
	free(tmp);
	if (!out)
	{
		free(help);
		return (NULL);
	}
	if (!ray_vec3d(ray, out))
	{
		out->x = point->x - help->x * 2;
		out->y = point->y - help->y * 2;
		out->z = point->z - help->z * 2;
	}
	free(help);
	return (out);
}

static t_vec3d	*is_closer(t_ray *ray, t_vec3d *point, double d)
{
	t_vec3d	*tmp;
	t_vec3d	*help;

	vec3d_norm(ray->dir);
	vec3d_mult(ray->dir, d / 2);
	help = create_vec3d(point->x - ray->dir->x, point->y - ray->dir->y, point->z - ray->dir->z);
	tmp = create_vec3d(point->x + ray->dir->x, point->y + ray->dir->y, point->z + ray->dir->z);
	if (vec3d_dist(tmp, ray->origin) > vec3d_dist(help, ray->origin))
	{
		free(tmp);
		return (help);
	}
	free(help);
	return (tmp);
}

/**
 * @brief calculates the intersecting point between a sphere and a ray
 * 
 * @param ray 
 * @param ball 
 * @return t_vec3d* 
 */
t_vec3d	*sphere_ray_inter(t_ray *ray, t_sphere *ball)
{
	double	dist;
	t_vec3d	*out;
	t_vec3d	*tmp;

	if (!ray || !ball)
		return (NULL);
	if (sphere_ray_touch(ray, ball) < 1)
		return (NULL);
	dist = ray_vec3d_dist(ray, ball->origin);
	out = closest_point(ray, ball->origin, dist);
	if (!out || cmp_d(dist, ball->d / 2))
		return (out);
	vec3d_norm(ray->dir);
	vec3d_mult(ray->dir, ball->d / 2);
	tmp = is_closer(ray, out, dist);
	free(out);
	return (tmp);
}
