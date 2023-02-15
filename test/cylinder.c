#include "test.h"

static int	util(t_cylinder *cyl, t_ray *ray, t_vec3d *expec)
{
	t_vec3d	*tmp;
	int		out;

	out = 1;
	tmp = cyl_ray_inter(cyl, ray);
	if (!vec3d_equal(tmp, expec))
		out = 0;
	destroy_cylinder(cyl);
	destroy_ray(ray);
	free(tmp);
	free(expec);
	return (out);
}

static int	test_on_axis(void)
{
	t_cylinder	*cyl;
	t_ray		*ray;

	cyl = create_cylinder(create_vec3d(2, 0, 0), create_vec3d(1, 0, 0), 4, 10);
	ray = create_dray(1, 0, 0, 0);
	if (!util(cyl, ray, create_vec3d(2, 0, 0)))
		return (0);
	cyl = create_cylinder(create_vec3d(2, 0, 0), create_vec3d(-1, 0, 0), 4, 10);
	ray = create_dray(1, 0, 0, 0);
	if (!util(cyl, ray, create_vec3d(2, 0, 0)))
		return (0);
	cyl = create_cylinder(create_vec3d(2, 0, 0), create_vec3d(1, 0, 0), 4, 10);
	ray = create_dray(-1, 0, 0, 0);
	if (!util(cyl, ray, create_vec3d(2, 0, 0)))
		return (0);
	cyl = create_cylinder(create_vec3d(-8, 0, 0), create_vec3d(1, 0, 0), 4, 10);
	ray = create_dray(1, 0, 0, 0);
	if (!util(cyl, ray, create_vec3d(2, 0, 0)))
		return (0);
	cyl = create_cylinder(create_vec3d(-8, 0, 0), create_vec3d(1, 0, 0), 4, 10);
	ray = create_dray(1, 0, 0, 0);
	if (!util(cyl, ray, create_vec3d(2, 0, 0)))
		return (0);
	return (1);
}

int	cyl_ray(void)
{
	t_cylinder	*cyl;
	t_ray		*ray;

	if (!test_on_axis())
		return (0);
	cyl = create_cylinder(create_vec3d(2, 2, 0), create_vec3d(1, 0, 0), 4, 10);
	ray = create_dray(1, 0, 0, 0);
	if (!util(cyl, ray, create_vec3d(2, 0, 0)))
		return (0);
	cyl = create_cylinder(create_vec3d(3, 3, 0), create_vec3d(1, 0, 0), 4, 10);
	ray = create_dray(1, 1, 0, 0);
	if (!util(cyl, ray, create_vec3d(3, 3, 0)))
		return (0);
	cyl = create_cylinder(create_vec3d(2, 2, 0), create_vec3d(1, 0, 0), 4, 10);
	ray = create_dray(1, 1, 0, 0);
	if (!util(cyl, ray, create_vec3d(2, 2, 0)))
		return (0);
	cyl = create_cylinder(create_vec3d(0, 8, 0), create_vec3d(1, 0, 0), 4, 10);
	ray = create_vray(create_vec3d(0, 0, 0), create_vec3d(1, 1, 0), 0);
	if (!util(cyl, ray, create_vec3d(10, 10, 0)))
		return (0);
	return (1);
}
