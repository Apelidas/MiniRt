#include "operations.h"

t_vec3d	*is_closer(t_ray *ray, t_vec3d *a, t_vec3d *b)
{
	t_vec3d	tmp;
	t_vec3d	help;

	tmp.x = a->x - ray->origin->x;
	tmp.y = a->y - ray->origin->y;
	tmp.z = a->z - ray->origin->z;
	help.x = b->x - ray->origin->x;
	help.y = b->y - ray->origin->y;
	help.z = b->z - ray->origin->z;
	if (vec3d_len(&help) > vec3d_len(&tmp))
	{
		free(b);
		return (a);
	}
	free(a);
	return (b);
}

static t_vec3d	*mantle_circle(t_ray *ray, t_cylinder *cyl, t_vec3d *a)
{
	t_vec3d	*help;
	t_vec3d	*norm;
	t_plane	*plane;

	help = vec3d_cross(ray->dir, cyl->norm);
	norm = vec3d_cross(cyl->norm, help);
	vec3d_norm(norm);
	vec3d_mult(norm, (cyl->d / 2));
	free(help);
	help = create_vec3d(cyl->origin->x + norm->x, cyl->origin->y + norm->y,
			cyl->origin->z + norm->z);
	plane = create_plane(help, norm, 0);
	help = cyl_plane_ray(ray, plane);
	norm = create_vec3d(cyl->origin->x - help->x, cyl->origin->y - help->y,
			cyl->origin->z - help->z);
	destroy_plane(plane);
	if (vec3d_angle(norm, cyl->norm) < 90)
		return (help);
	free(norm);
	norm = create_vec3d(cyl->origin->x + help->x, cyl->origin->y + help->y,
			cyl->origin->z + help->z);
	free(help);
	return (is_closer(ray, a, norm));
}

static t_vec3d	*mantle_help(t_ray *ray, t_cyl *cyl, t_vec3d *a, double dist)
{
	double	angle;
	t_vec3d	*help;

	angle = vec3d_angle(a, cyl->norm);
	if (angle > 90)
	{
		free(a);
		return (NULL);
	}
	if (dist / sin(angle) > cyl->h)
	{
		free(a);
		return (NULL);
	}
	dist = (cyl->d / 2) - dist;
	angle = vec3d_angle(ray->dir, cyl->norm);
	dist = dist / sin(angle);
	vec3d_norm(ray->dir);
	vec3d_mult(ray->dir, dist);
	help = is_closer(ray, vec3d_add(a, ray->dir), vec3d_sub(a, ray->dir));
	free(a);
	return (help);
}

static t_vec3d	*mantle(t_ray *ray, t_cylinder *cyl)
{
	t_plane	*help;
	t_vec3d	*a;
	t_vec3d	*b;
	double	dist;

	a = vec3d_cross(ray->dir, cyl->norm);
	b = vec3d_cross(cyl->norm, a);
	help = create_plane(cyl->origin, b, 0);
	free(a);
	a = plane_ray_inter(ray, help);
	free(help);
	dist = cyl_dist(a, cyl);
	free(b);
	if (dist > cyl->d / 2)
	{
		free(a);
		return (NULL);
	}
	if (cmp_d(dist, cyl->d / 2))
		return (a);
	if (cmp_d(dist, 0))
	{
		dist = (cyl->d / 2) / sin(vec3d_angle(ray->dir, cyl->norm));
		vec3d_norm(ray->dir);
		vec3d_mult(ray->dir, dist);
		b = is_closer(ray, vec3d_add(a, ray->dir), vec3d_sub(a, ray->dir));
		free(a);
		return (b);
	}
	return (mantle_help(ray, cyl, a, dist));
}

t_vec3d	*cyl_ray_inter(t_cylinder *cyl, t_ray *ray)
{
	t_vec3d	*tmp;
	t_vec3d	*a;
	t_vec3d	*b;

	vec3d_norm(cyl->norm);
	vec3d_mult(cyl->norm, cyl->h);
	tmp = create_vec3d(cyl->origin->x + cyl->norm->x, cyl->origin->y
			+ cyl->norm->y, cyl->origin->z + cyl->norm->z);
	a = ray_circle_inter(ray, cyl->norm, cyl->origin, cyl->d / 2);
	b = ray_circle_inter(ray, cyl->norm, tmp, cyl->d / 2);
	free(tmp);
	if (a && b)
		return (on_ray(ray, a, b));
	if (a && !b)
		return (mantle_circle(ray, cyl, a));
	if (!a && b)
	{
		cylinder_reverse(cyl);
		return (mantle_circle(ray, cyl, b));
	}
	return (mantle(ray, cyl));
}
