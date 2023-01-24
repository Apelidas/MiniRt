
#include "operations.h"

t_ray	*create_ray(void)
{
	t_ray	*out;

	out = malloc(sizeof(t_ray));
	if (!out)
		return (NULL);
	out->origin = create_vec3d(0.0, 0.0, 0.0);
	if (!out->origin)
	{
		free(out);
		return (NULL);
	}
	out->dir = create_vec3d(1, 1, 1);
	if (!out->origin)
	{
		free(out->origin);
		free(out);
		return (NULL);
	}
	out->trgb = 0;
	return (out);
}

t_ray	*create_oray(double x, double y, double z)
{
	t_ray	*out;

	out = create_ray();
	if (!out)
		return (NULL);
	out->origin->x = x;
	out->origin->y = y;
	out->origin->z = z;
	return (out);
}

t_ray	*create_dray(double x, double y, double z, int trgb)
{
	t_ray	*out;

	out = create_ray();
	if (!out)
		return (NULL);
	out->dir->x = x;
	out->dir->y = y;
	out->dir->z = z;
	out->trgb = trgb;
	return (out);
}

t_ray	*create_vray(t_vec3d *origin, t_vec3d *dir, int trgb)
{
	t_ray	*out;

	out = create_ray();
	if (!out)
		return (NULL);
	free(out->origin);
	free(out->dir);
	out->origin = origin;
	out->dir = dir;
	out->trgb = trgb;
	return (out);
}

void	destroy_ray(t_ray *todel)
{
	if (!todel)
		return ;
	if (todel->dir)
		free(todel->dir);
	if (todel->origin)
		free(todel->origin);
	free(todel);
}
