#include "operations.h"

t_cylinder	*create_cylinder(t_vec3d *origin, t_vec3d *n, double d, double h)
{
	t_cylinder	*out;

	out = malloc(sizeof(t_cylinder));
	if (!out)
		return (NULL);
	out->origin = origin;
	out->norm = n;
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
