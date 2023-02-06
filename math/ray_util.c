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
	t_vec3d	*tmp;

	if (!a || !b)
		return (-1);
	if (!vec3d_equal(a->origin, b->origin))
		return (0);
	tmp = create_vec3d(a->origin->x + a->dir->x, a->origin->y + a->dir->y,
			a->origin->z + a->dir->z);
	if (!ray_vec3d(b, tmp))
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	if (a->trgb != b->trgb)
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

/**
 * @brief calulates the distance from a point to a ray
 * 
 * @param ray 
 * @param point 
 * @return double 
 */
double	ray_vec3d_dist(t_ray *ray, t_vec3d *point)
{
	t_vec3d	*tmp;
	t_vec3d	*help;
	double	out;

	if (!ray || !point)
		return (-1);
	if (ray_vec3d(ray, point))
		return (0);
	tmp = create_vec3d(point->x - ray->origin->x,
			point->y - ray->origin->y, point->z - ray->origin->z);
	out = vec3d_angle(tmp, ray->dir);
	if (out > 90)
	{
		free(tmp);
		return (vec3d_dist(ray->origin, point));
	}
	help = vec3d_cross(tmp, ray->dir);
	out = vec3d_len(help);
	out = out / vec3d_len(ray->dir);
	free(tmp);
	free(help);
	return (out);
}

t_vec3d	*ray_circle_inter(t_ray *ray, t_vec3d *n, t_vec3d *o, double rad)
{
	t_vec3d	*help;
	t_vec3d	*rev_help;
	t_plane	*tmp;
	t_ray	*rev;

	tmp = create_plane(o, n, 0);
	help = plane_ray_inter(ray, tmp);
	rev = ray_rev(ray);
	rev_help = plane_ray_inter(rev, tmp);
	destroy_ray(rev);
	free(tmp);
	if (!help && !rev_help)
		return (NULL);
	if (help && vec3d_dist(help, o) <= rad && ray_vec3d(ray, help))
	{
		free(rev_help);
		return (help);
	}
	free(help);
	if (rev_help && vec3d_dist(rev_help, o) <= rad && ray_vec3d(ray, rev_help))
		return (rev_help);
	free(rev_help);
	return (NULL);
}
