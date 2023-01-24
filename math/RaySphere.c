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
	t_vec3d	*tmp;
	t_vec3d	*help;
	t_vec3d	*out;

	help = ray->origin;
	tmp = create_vec3d(help->x - point->x,
			help->y - point->y, help->z - point->z);
	help = vec3d_cross(tmp, ray->dir);
	free(tmp);
	tmp = vec3d_cross(help, ray->dir);
	vec3d_norm(tmp);
	vec3d_mult(tmp, dist);
	out = create_vec3d(tmp->x + point->x, tmp->y + point->y, tmp->z + point->z);
	if (!ray_vec3d(ray, out))
	{
		out->x -= tmp->x * 2;
		out->y -= tmp->y * 2;
		out->z -= tmp->z * 2;
	}
	free(tmp);
	free(help);
	return (out);
}

static t_vec3d	*inter(t_ray *ray, t_sphere *ball, double dist, t_vec3d *point)
{
	double	len;
	t_vec3d	*a;
	t_vec3d	*b;

	if (cmp_d(dist, ball->d / 2))
		len = dist;
	else
		len = sqrt((pow(ball->d / 2, 2) - pow(dist, 2)));
	vec3d_norm(ray->dir);
	vec3d_mult(ray->dir, len);
	a = create_vec3d(point->x + ray->dir->x,
			point->y + ray->dir->y, point->z + ray->dir->z);
	b = create_vec3d(point->x - ray->dir->x,
			point->y - ray->dir->y, point->z - ray->dir->z);
	if (vec3d_dist(a, ray->origin) > vec3d_dist(b, ray->origin))
	{
		free(a);
		return (b);
	}
	free(b);
	return (a);
}

/**
 * @brief 
 * calculates the intersecting point between a sphere and a ray
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
	if (cmp_d(dist, 0))
	{
		out = inter(ray, ball, ball->d / 2, ball->origin);
		return (out);
	}
	tmp = closest_point(ray, ball->origin, dist);
	if (cmp_d(vec3d_dist(tmp, ball->origin), ball->d / 2))
		return (tmp);
	out = inter(ray, ball, dist, tmp);
	free(tmp);
	return (out);
}
