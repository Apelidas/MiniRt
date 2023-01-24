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