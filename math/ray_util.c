
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
	help = vec3d_cross(tmp, ray->dir);
	out = vec3d_len(help);
	out = out / vec3d_len(ray->dir);
	free(tmp);
	free(help);
	return (out);
}
