
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
	if (!on_ray(a, b->origin))
		return (0);
	vec3d_norm(a->dir);
	vec3d_norm(b->dir);
	if (!vec3d_equal(a->dir, b->dir))
		return (0);
	if (a->trgb != b->trgb)
		return (0);
	return (1);
}

int	ray_on(t_ray *ray, t_vec3d *point)
{
	double	a;
	double	b;
	double	c;

	if (!ray || !point)
		return (-1);
	a = (point->x - ray->origin->x) / ray->dir->x;
	b = (point->y - ray->origin->y) / ray->dir->y;
	c = (point->z - ray->origin->z) / ray->dir->z;
	if (!cmp_d(a, b) || !cmp_d(a, c))
		return (0);
	return (1);
}