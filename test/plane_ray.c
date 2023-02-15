#include "test.h"

static int	util(t_ray *a, t_plane *plane, int (*test)(t_ray*, t_plane*))
{
	if (!test(a, plane))
	{
		destroy_ray(a);
		destroy_plane(plane);
		return (0);
	}
	destroy_ray(a);
	destroy_plane(plane);
	return (1);
}

int	p_ray_in(void)
{
	t_ray	*tmp;
	t_plane	*help;

	tmp = create_dray(0, 1, 1, 0);
	help = create_plane(create_vec3d(0, 0, 0), create_vec3d(1, 0, 0), 0);
	if (!util(tmp, help, &plane_ray_in))
		return (0);
	tmp = create_dray(0, 1.1234, 1.1234, 0);
	help = create_plane(create_vec3d(0, 0, 0), create_vec3d(1, 0, 0), 0);
	if (!util(tmp, help, &plane_ray_in))
		return (0);
	tmp = create_dray(0, -1.1234, 1.1234, 0);
	help = create_plane(create_vec3d(0, 0, 0), create_vec3d(1, 0, 0), 0);
	if (!util(tmp, help, &plane_ray_in))
		return (0);
	tmp = create_dray(0, 1.1234, 21, 0);
	help = create_plane(create_vec3d(0, 0, 0), create_vec3d(1, 0, 0), 0);
	if (!util(tmp, help, &plane_ray_in))
		return (0);
	tmp = create_dray(0, -1.1234, 21, 0);
	help = create_plane(create_vec3d(0, 0, 0), create_vec3d(1, 0, 0), 0);
	if (!util(tmp, help, &plane_ray_in))
		return (0);
	return (1);
}

int	p_ray_touch(void)
{
	t_ray	*tmp;
	t_plane	*help;

	tmp = create_vray(create_vec3d(1, 0, 0), create_vec3d(1, 1, 0), 0);
	help = create_plane(create_vec3d(0, 0, 0), create_vec3d(1, 0, 0), 0);
	if (util(tmp, help, &plane_ray_touch))
		return (0);
	tmp = create_dray(0, 1, 1, 0);
	help = create_plane(create_vec3d(0, 0, 0), create_vec3d(1, 0, 0), 0);
	if (util(tmp, help, &plane_ray_touch))
		return (0);
	tmp = create_dray(0, 1, 2, 0);
	help = create_plane(create_vec3d(0, 0, 0), create_vec3d(1, 0, 0), 0);
	if (util(tmp, help, &plane_ray_touch))
		return (0);
	tmp = create_vray(create_vec3d(5, 5, 5), create_vec3d(1, 0, 0), 0);
	help = create_plane(create_vec3d(0, 0, 0), create_vec3d(1, 0, 0), 0);
	if (util(tmp, help, &plane_ray_touch))
		return (0);
	tmp = create_vray(create_vec3d(5, 5, 5), create_vec3d(1, 2, 3), 0);
	help = create_plane(create_vec3d(0, 0, 0), create_vec3d(1, 0, 0), 0);
	if (util(tmp, help, &plane_ray_touch))
		return (0);
	return (1);
}

static int	util_inter(t_ray *a, t_plane *b, t_vec3d *cmp)
{
	t_vec3d	*tmp;

	tmp = plane_ray_inter(a, b);
	if (!vec3d_equal(tmp, cmp) || vec3d_equal(tmp, cmp) == -1)
	{
		destroy_ray(a);
		destroy_plane(b);
		if (cmp)
			free(cmp);
		if (tmp)
			free(tmp);
		return (0);
	}
	destroy_ray(a);
	destroy_plane(b);
	if (cmp)
		free(cmp);
	if (tmp)
		free(tmp);
	return (1);
}

int	p_ray_inter(void)
{
	t_ray	*tmp;
	t_plane	*help;

	tmp = create_dray(0, 1, 1, 0);
	help = create_plane(create_vec3d(0, 0, 0), create_vec3d(1, 0, 0), 0);
	if (!util_inter(tmp, help, NULL))
		return (0);
	tmp = create_dray(1, 2, 3, 0);
	help = create_plane(create_vec3d(0, 0, 0), create_vec3d(1, 0, 0), 0);
	if (!util_inter(tmp, help, create_vec3d(0, 0, 0)))
		return (0);
	tmp = create_vray(create_vec3d(5, 5, 5), create_vec3d(1, 0, 0), 0);
	help = create_plane(create_vec3d(0, 0, 0), create_vec3d(1, 0, 0), 0);
	if (!util_inter(tmp, help, NULL))
		return (0);
	tmp = create_vray(create_vec3d(5, 5, 5), create_vec3d(1, 2, 3), 0);
	help = create_plane(create_vec3d(0, 0, 0), create_vec3d(1, 0, 0), 0);
	if (!util_inter(tmp, help, NULL))
		return (0);
	tmp = create_vray(create_vec3d(5, 5, 5), create_vec3d(0, 1, 1), 0);
	help = create_plane(create_vec3d(0, 0, 0), create_vec3d(1, 0, 0), 0);
	if (util_inter(tmp, help, create_vec3d(5, 0, 0)))
		return (0);
	return (1);
}
