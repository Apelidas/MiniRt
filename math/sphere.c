#include "operations.h"

void	destroy_sphere(t_sphere *del)
{
	if (!del)
		return ;
	if (del->origin)
		free(del->origin);
	free(del);
}

/*
checks if point is on the sphere
*/
int	sphere_point(t_vec3d *point, t_sphere *ball)
{
	if ((pow(point->x, 2) - pow(ball->origin->x, 2)) != (pow(ball->d, 2) / 4))
		return (0);
	if ((pow(point->y, 2) - pow(ball->origin->y, 2)) != (pow(ball->d, 2) / 4))
		return (0);
	if ((pow(point->z, 2) - pow(ball->origin->z, 2)) != (pow(ball->d, 2) / 4))
		return (0);
	return (1);
}

int	sphere_inside(t_sphere *sphere, t_camera *cam)
{
	if (vec3d_dist(sphere->origin, cam->pos) < sphere->d / 2)
		return (1);
	return (0);
}

void	sphere_intersection_norm(double c[3], t_sphere *sphr, t_ray *ray)
{
	t_vec3d	*tmp;

	tmp = vec3d_minus(ray->origin, sphr->origin);
	c[0] = vec3d_dot(ray->dir, ray->dir);
	c[1] = 2 * vec3d_dot(ray->dir, tmp);
	c[2] = vec3d_dot(tmp, tmp) - pow(sphr->d / 2, 2);
	free(tmp);
}

double	sphere_intersection(t_ray *ray, t_sphere *sphr)
{
	double	c[3];
	double	delta;
	double	t1;
	double	t2;

	sphere_intersection_norm(c, sphr, ray);
	delta = pow(c[1], 2) - 4 * c[0] * c[2];
	if (delta < 0)
		return (-1);
	t1 = (-c[1] + sqrt(delta)) / (2 * c[0]);
	t2 = (-c[1] - sqrt(delta)) / (2 * c[0]);
	if (t1 >= 0 && t2 >= 0)
	{
		if (t1 > t2)
			return (t2);
		return (t1);
	}
	else if (t1 >= 0)
		return (t1);
	else if (t2 >= 0)
		return (t2);
	return (-1);
}
