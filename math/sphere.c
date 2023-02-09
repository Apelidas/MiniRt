#include "operations.h"

t_sphere	*create_sphere(t_vec3d *origin, double diameter, int trgb)
{
	t_sphere	*out;

	out = malloc(sizeof(t_sphere));
	if (!out)
		return (NULL);
	out->origin = origin;
	out->d = diameter;
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


t_ray	*sphere_reflect(t_ray *ray_in, t_sphere *sphere, t_vec3d *point)
{
	t_ray	*out;
	t_vec3d	*norm;

	norm = vec3d_sub(point, sphere->origin);
	out = create_vray(vec3d_cpy(point), vec3d_sub(ray_in->dir, norm));
	free(norm);
	return (out);
}