#include "operations.h"

t_sphere	*create_sphere(t_vec3d *origin, double dia, int trgb)
{
	t_sphere	*out;

	out = malloc(sizeof(t_sphere));
	if (!out)
		return (NULL);
	out->origin = origin;
	out->d = dia;
	out->trgb = trgb;
	return (out);
}

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
