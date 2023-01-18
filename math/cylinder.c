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

void	destroy_cylinder(t_cylinder *cyl)
{
	if (!cyl)
		return ;
	if (cyl->origin)
		free(cyl->origin);
	if (cyl->norm)
		free(cyl->norm);
	free(cyl);
}

static int	cyl_ray_equal(t_cylinder *cyl, t_ray *ray)
{
	t_ray *tmp;

	tmp = create_vray(vec3d_cpy(cyl->origin), vec3d_cpy(cyl->norm), 0);
	if (ray_equal(ray, tmp))
	{
		destroy_ray(tmp);
		return (1);
	}
	destroy_ray(tmp);
	return (0);
}

static t_vec3d	*is_closer(t_vec3d *point, double dist, t_ray *ray)
{
	t_vec3d	*a;
	t_vec3d	*b;

	vec3d_norm(ray->dir);
	vec3d_mult(ray->dir, dist);
	a = create_vec3d(point->x - ray->dir->x, point->y - ray->dir->y, point->z - ray->dir->z);
	b = create_vec3d(point->x + ray->dir->x, point->y + ray->dir->y, point->z + ray->dir->z);
	if (vec3d_dist(a, ray->origin) > vec3d_dist(b, ray->origin))
	{
		free(a);
		return (b);
	}
	free(b);
	return (a);
}

static t_vec3d	*parallel_util(t_cylinder *cyl, t_ray *ray, t_vec3d *orig)
{
	t_vec3d	*norm;
	t_vec3d	*help;
	t_vec3d	*tmp;

	norm = cyl->origin;
	help = create_vec3d(norm->x - ray->origin->x, norm->y - ray->origin->y, norm->z - ray->origin->z);
	norm = vec3d_cross(help, ray->dir);
	free(help);
	help = vec3d_cross(norm, ray->dir);
	free(norm);
	norm = help;
	vec3d_norm(norm);
	vec3d_mult(norm, cyl->d / 2);
	help = create_vec3d(orig->x - norm->x, orig->y - norm->y, orig->z - norm->z);
	tmp = create_vec3d(orig->x + norm->x, orig->y + norm->y, orig->z + norm->z);
	free(norm);
	if (ray_vec3d(ray, tmp))
	{
		free(help);
		return (tmp);
	}
	free(tmp);
	return (help);
}

static t_vec3d	*parallel(t_cylinder *cyl, t_ray *ray)
{
	t_vec3d	*tmp;
	t_vec3d	*out;
	double	dist;

	vec3d_mult(cyl->norm, cyl->h);
	tmp = create_vec3d(cyl->origin->x + cyl->norm->x, cyl->origin->y + cyl->norm->y, cyl->origin->z + cyl->norm->z);
	if (cyl_ray_equal(cyl, ray))
	{
		if (vec3d_dist(tmp, ray->origin) > vec3d_dist(cyl->origin, ray->origin))
		{
			free(tmp);
			return (vec3d_cpy(cyl->origin));
		}
		return (tmp);
	}
	dist = ray_vec3d_dist(ray, cyl->origin);
	if (dist > cyl->d / 2)
	{
		free(tmp);
		return (NULL);
	}
	out = parallel_util(cyl, ray, tmp); //doesn´t work because 90°
	free(tmp);
	tmp = parallel_util(cyl, ray, cyl->origin);
	if (vec3d_dist(out, ray->origin) > vec3d_dist(tmp, ray->origin))
	{
		free(out);
		return (tmp);
	}
	free(tmp);
	return (out);
}

t_vec3d	*cyl_ray_inter(t_cylinder *cyl, t_ray *ray)
{
	t_vec3d	*help;
	t_vec3d	*out;
	t_plane	*tmp;
	t_ray	*a;
	double	dist;

	if (!cyl || !ray)
		return (NULL);
	vec3d_norm(ray->dir);
	vec3d_norm(cyl->norm);
	print_vec3d(ray->dir);
	print_vec3d(cyl->norm);
	if (vec3d_vec3d_equal(ray->dir, cyl->norm))
		return (parallel(cyl, ray));
	tmp = create_plane(vec3d_cpy(cyl->origin), vec3d_cpy(ray->dir), 0);
	help = plane_ray_inter(ray, tmp);
	a = create_vray(vec3d_cpy(cyl->origin), vec3d_cpy(cyl->norm), 0);
	dist = ray_vec3d_dist(a, help);
	destroy_plane(tmp);
	destroy_ray(a);
	if (dist > cyl->d / 2)
	{
		free(help);
		return (NULL);
	}
	if (cmp_d(dist, cyl->d / 2))
		return (help);
	dist = sqrt(pow(cyl->d / 2, 2) - pow(dist, 2));
	out = is_closer(help, dist, ray);
	free(help);
	return (out);
}