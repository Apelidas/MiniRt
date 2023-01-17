#include "test.h"

static int	touch_util(t_sphere *ball, t_ray *ray, int expected)
{
	if (sphere_ray_touch(ray, ball) != expected)
	{
		destroy_sphere(ball);
		destroy_ray(ray);
		return (0);
	}
	destroy_sphere(ball);
	destroy_ray(ray);
	return (1);
}

int	sr_touch(void)
{
	t_sphere	*ball;
	t_ray		*ray;

	ray = create_vray(create_vec3d(0, 0, 0), create_vec3d(1, 0, 0), 0);
	ball = create_sphere(create_vec3d(0, 0, 0), 2, 0);
	if (!touch_util(ball, ray, 1))
		return (0);
	ray = create_vray(create_vec3d(0, 0, 0), create_vec3d(1, 0, 0), 0);
	ball = create_sphere(create_vec3d(1, 0, 0), 2, 0);
	if (!touch_util(ball, ray, 1))
		return (0);
	ray = create_vray(create_vec3d(0, 0, 0), create_vec3d(1, 0, 0), 0);
	ball = create_sphere(create_vec3d(1, 1, 0), 2, 0);
	if (!touch_util(ball, ray, 1))
		return (0);
	ray = create_vray(create_vec3d(0, 0, 0), create_vec3d(1, 0, 0), 0);
	ball = create_sphere(create_vec3d(1, 2, 0), 2, 0);
	if (!touch_util(ball, ray, 1))
		return (0);
	ray = create_vray(create_vec3d(0, 0, 0), create_vec3d(1, 0, 0), 0);
	ball = create_sphere(create_vec3d(0, 3, 0), 2, 0);
	if (!touch_util(ball, ray, 0))
		return (0);
	return (1);
}

static int	inter_util(t_sphere *ball, t_ray *ray, t_vec3d *expec)
{
	t_vec3d	*tmp;
	int		out;

	tmp = sphere_ray_inter(ray, ball);
	out = 1;
	if (!vec3d_equal(expec, tmp))
		out = 0;
	destroy_sphere(ball);
	destroy_ray(ray);
	free(expec);
	free(tmp);
	return (out);
}

int	sr_inter(void)
{
	t_sphere	*ball;
	t_ray		*ray;

	ray = create_vray(create_vec3d(0, 0, 0), create_vec3d(1, 0, 0), 0);
	ball = create_sphere(create_vec3d(2, 0, 0), 2, 0);
	if (!inter_util(ball, ray, create_vec3d(0, 0, 0)))
		return (0);
	ray = create_vray(create_vec3d(0, 0, 0), create_vec3d(1, 0, 0), 0);
	ball = create_sphere(create_vec3d(2, 0, 0), 1, 0);
	if (!inter_util(ball, ray, create_vec3d(1, 0, 0)))
		return (0);
	ray = create_vray(create_vec3d(0, 0, 0), create_vec3d(1, 0, 0), 0);
	ball = create_sphere(create_vec3d(2, 4, 0), 2, 0);
	if (!inter_util(ball, ray, NULL))
		return (0);
	ray = create_vray(create_vec3d(0, 0, 0), create_vec3d(1, 0, 0), 0);
	ball = create_sphere(create_vec3d(2, 2, 0), 2, 0);
	if (!inter_util(ball, ray, create_vec3d(2, 0, 0)))
		return (0);
	ray = create_vray(create_vec3d(0, 0, 0), create_vec3d(1, 0, 0), 0);
	ball = create_sphere(create_vec3d(3.73205, 1, 0), 2, 0);
	if (!inter_util(ball, ray, create_vec3d(2, 0, 0)))
		return (0);
	return (1);
}