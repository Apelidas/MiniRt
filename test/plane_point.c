#include "test.h"

static int	util(t_plane *a, t_vec3d *b)
{
	if (!plane_point(b, a))
	{
		destroy_plane(a);
		free(b);
		return (0);
	}
	destroy_plane(a);
	free(b);
	return (1);
}

int	p_point(void)
{
	t_plane	*tmp;

	tmp = create_plane(create_vec3d(0, 0, 0), create_vec3d(1, 0, 0), 0);
	if (!util(tmp, create_vec3d(0, 1, 1)))
		return (0);
	tmp = create_plane(create_vec3d(0, 0, 0), create_vec3d(1, 0, 0), 0);
	if (!util(tmp, create_vec3d(0, 0, 0)))
		return (0);
	tmp = create_plane(create_vec3d(0, 0, 0), create_vec3d(1, 0, 0), 0);
	if (!util(tmp, create_vec3d(0,12.34, 8.6)))
		return (0);
	tmp = create_plane(create_vec3d(0, 0, 0), create_vec3d(1, 0, 0), 0);
	if (util(tmp, create_vec3d(1, 1, 1)))
		return (0);
	return (1);
}