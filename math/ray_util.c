
#include "operations.h"

t_ray	*ray_cpy(t_ray *in)
{
	t_ray	*out;

	out = create_vray(vec3d_cpy(in->origin), vec3d_cpy(in->dir), in->trgb);
	if (!out)
		return (NULL);
	return (out);
}

int	ray_equal(t_ray *a, t_ray *b)
{
	if (!a || !b)
		return (-1);
	if (!ray_vec3d(a, b->origin))
		return (0);
	vec3d_norm(a->dir);
	vec3d_norm(b->dir);
	if (!vec3d_equal(a->dir, b->dir))
		return (0);
	if (a->trgb != b->trgb)
		return (0);
	return (1);
}

int	ray_vec3d(t_ray *ray, t_vec3d *point)
{
	double	a;
	double	b;
	double	c;

	if (!ray || !point)
		return (-1);
	a = 0;
	b = 0;
	c = 0;
	if (!cmp_d(ray->dir->x, 0))
		a = (point->x - ray->origin->x) / ray->dir->x;
	else
		a = (point->x - ray->origin->x);
	if (!cmp_d(ray->dir->y, 0))
		b = (point->y - ray->origin->y) / ray->dir->y;
	else
		b = (point->y - ray->origin->y);
	if (!cmp_d(ray->dir->z, 0))
		c = (point->z - ray->origin->z) / ray->dir->z;
	else
		c = (point->z - ray->origin->z);
	if (!cmp_d(ray->dir->x, 0) && !cmp_d(ray->dir->y, 0))
		if (!cmp_d(a, b))
			return (0);
	if (!cmp_d(ray->dir->x, 0) && !cmp_d(ray->dir->z, 0))
		if (!cmp_d(a, c))
			return (0);
	if (!cmp_d(ray->dir->y, 0) && !cmp_d(ray->dir->z, 0))
		if (!cmp_d(b, c))
			return (0);
	if (cmp_d(ray->dir->x, 0))
		if (!cmp_d(ray->origin->x, point->x))
			return (0);
	if (cmp_d(ray->dir->y, 0))
		if (!cmp_d(ray->origin->y, point->y))
			return (0);
	if (cmp_d(ray->dir->z, 0))
		if (!cmp_d(ray->origin->z, point->z))
			return (0);
	return (1);
}

/*
calculates the angle between 2 rays
only works if 2 ray are intersecting
returns -1 (value < 0) if error
*/
double	ray_angle(t_ray *a, t_ray *b)
{
	double	out;

	if (!a || !b)
		return (-1);
	out = vec3d_angle(a->dir, b->dir);
	return (out);
}

// double	ray_vec3d_dist(t_ray *)