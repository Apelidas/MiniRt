#include "operations.h"

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
