#include "operations.h"

t_cylinder	*create_cylinder(t_vec3d *origin, t_vec3d *norm, double d, double h)
{
	t_cylinder	*out;

	out = malloc(sizeof(t_cylinder));
	if (!out)
		return (NULL);
	out->origin = origin;
	out->norm = norm;
	out->d = d;
	out->h = h;
	return (out);
}

void	destroy_cylinder(t_cylinder *cyl)
{
	if (!cyl)
		return ;
	if (cyl->origin)
		free(cyl->origin);
	if (cyl->norm)
		free(cyl->norm);
	free(cyl);
}

void	cylinder_reverse(t_cylinder *cyl)
{
	vec3d_norm(cyl->norm);
	vec3d_mult(cyl->norm, cyl->h);
	cyl->origin->x += cyl->norm->x;
	cyl->origin->y += cyl->norm->y;
	cyl->origin->z += cyl->norm->z;
	cyl->norm->x *= -1;
	cyl->norm->y *= -1;
	cyl->norm->z *= -1;
}

double	cyl_dist(t_vec3d *inter, t_cylinder *cyl)
{
	t_ray	*help;
	double	dist;

	help = create_vray(cyl->origin, cyl->norm, 0);
	dist = ray_vec3d_dist(help, inter);
	free(help);
	return (dist);
}

t_vec3d	*on_ray(t_ray *ray, t_vec3d *a, t_vec3d *b)
{
	int	ra;
	int	rb;

	ra = ray_vec3d(ray, a);
	rb = ray_vec3d(ray, b);
	if (ra && rb)
		return (is_closer(ray, a, b));
	if (ra && !rb)
	{
		free(b);
		return (a);
	}
	if (!ra && rb)
	{
		free(a);
		return (b);
	}
	free(a);
	free(b);
	return (NULL);
}
