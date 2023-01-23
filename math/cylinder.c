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

void	cylinder_reverse(t_cylinder *cyl)
{
	vec3d_norm(cyl->norm);
	vec3d_mult(cyl->norm, cyl->h);
	cyl->origin->x += cyl->norm->x;
	cyl->origin->y += cyl->norm->y;
	cyl->origin->z += cyl->norm->z;
	cyl->norm->x *= -1;
	cyl->norm->y *= -1;
	cyl->norm->z *= -1;
}

t_vec3d	*ray_circle_inter(t_ray *ray, t_vec3d *norm, t_vec3d *origin, double rad)
{
	t_vec3d	*help;
	t_plane	*tmp;

	tmp = create_plane(origin, norm, 0);
	help = plane_ray_inter(ray, tmp);
	free(tmp);
	if (!help)
		return (NULL);
	if (vec3d_dist(help, origin) <= rad)
		return (help);
	free(help);
	return (NULL);
}

static t_vec3d	*is_closer(t_ray *ray, t_vec3d *a, t_vec3d *b)
{
	t_vec3d	tmp;
	t_vec3d	help;

	tmp->x = a->x - ray->origin->x;
	tmp->y = a->y - ray->origin->y;
	tmp->z = a->z - ray->origin->z;
	help->x = b->x - ray->origin->x;
	help->y = b->y - ray->origin->y;
	help->z = b->z - ray->origin->z;
	if (vec3d_len(help) > vec3d_len(tmp))
	{
		free(b);
		return (a);
	}
	free(a);
	return (b);
}

static t_vec3d	*on_ray(t_ray *ray, t_vec3d *a, t_vec3d *b)
{
	int	ra;
	int	rb;
	
	ra = ray_vec3d(ray, a);
	rb = ray_vec3d(ray, b);
	if (ra && rb)
		return (is_closer(ray, a, b));
	if (ra && !rb)
	{
		free(b);
		return (a);
	}
	if (!ra && rb)
	{
		free(a);
		return (b);
	}
	free(a);
	free(b);
	return (NULL);
}

static t_vec3d	*mantle_circle(t_ray *ray, t_cylinder *cyl, t_vec3d *a)
{
	t_vec3d	*help;
	t_vec3d	*norm;
	t_plane	*plane;

	help = vec3d_cross(ray->dir, cyl->norm);
	norm = vec3d_cross(cyl->norm, help);
	vec3d_norm(norm);
	vec3d_mult(norm, cyl->d / 2);
	free(help);
	help = create_vec3d(cyl->origin->x + norm->x, cyl->origin->y + norm->y, cyl->origin->z + norm->z);
	plane = create_plane(help, norm, 0);
	help = plane_ray_inter(ray, plane);
	norm = create_vec3d(cyl->origin->x - help->x, cyl->origin->y - help->y, cyl->origin->z - help->z);
	destroy_plane(plane);
	if (vec3d_angle(norm, cyl->norm) < 90)
		return (help);
	free(norm);
	free(help);
	norm = create_vec3d(cyl->origin->x + help->x, cyl->origin->y + help->y, cyl->origin->z + help->z);
	return (is_closer(ray, a, norm));
}

static t_vec3d	*mantle(t_ray *ray, t_cylinder *cyl)
{
	t_plane	*help;
	t_plane	*tmp;
	t_vec3d	*a;
	t_vec3d	*b;
	double	max;

	max = sqrt(pow(cyl->d / 2, 2) + cyl->h * cyl->h);
	vec3d_norm(ray->dir);
	vec3d_mult(ray->dir, cyl->d / 2);
	a = create_vec3d(cyl->origin->x + ray->dir->x, cyl->origin->y + ray->dir->y, cyl->origin->z + ray->dir->z);
	b = create_vec3d(cyl->origin->x - ray->dir->x, cyl->origin->y - ray->dir->y, cyl->origin->z - ray->dir->z);
	help = create_plane(a, vec3d_cpy(ray->dir), 0);
	tmp = create_plane(b, vec3d_cpy(ray->dir), 0);
	a = plane_ray_inter(ray, help);
	destroy_plane(help);
	b = plane_ray_inter(ray, tmp);
	destroy_plane(tmp);
	if (!a)
		return (NULL);

	

}

t_vec3d	*cyl_ray_inter(t_cylinder *cyl, t_ray *ray)
{
	t_vec3d	*tmp;
	t_vec3d	*a;
	t_vec3d	*b;

	vec3d_norm(cyl->norm);
	vec3d_mult(cyl->norm, cyl->h);
	tmp = create_vec3d(cyl->origin->x + cyl->norm->x, cyl->origin->y + cyl->norm->y, cyl->origin->z + cyl->norm->z);
	a = ray_circle_inter(ray, cyl->norm, cyl->origin, cyl->d);
	b = ray_circle_inter(ray, cyl->norm, tmp, cyl->d);
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















// static int	cyl_ray_equal(t_cylinder *cyl, t_ray *ray)
// {
// 	t_ray *tmp;

// 	tmp = create_vray(vec3d_cpy(cyl->origin), vec3d_cpy(cyl->norm), 0);
// 	if (ray_equal(ray, tmp))
// 	{
// 		destroy_ray(tmp);
// 		return (1);
// 	}
// 	destroy_ray(tmp);
// 	return (0);
// }

// static t_vec3d	*is_closer(t_vec3d *point, double dist, t_ray *ray)
// {
// 	t_vec3d	*a;
// 	t_vec3d	*b;

// 	vec3d_norm(ray->dir);
// 	vec3d_mult(ray->dir, dist);
// 	a = create_vec3d(point->x - ray->dir->x, point->y - ray->dir->y, point->z - ray->dir->z);
// 	b = create_vec3d(point->x + ray->dir->x, point->y + ray->dir->y, point->z + ray->dir->z);
// 	print_vec3d(point);
// 	write(1, "a:\n", 3);
// 	print_vec3d(a);
// 	write(1, "b:\n", 3);
// 	print_vec3d(b);
// 	if (vec3d_dist(a, ray->origin) > vec3d_dist(b, ray->origin))
// 	{
// 		free(a);
// 		return (b);
// 	}
// 	free(b);
// 	return (a);
// }

// static t_vec3d	*parallel_util(t_cylinder *cyl, t_ray *ray, t_vec3d *orig)
// {
// 	t_vec3d	*norm;
// 	t_vec3d	*help;
// 	t_vec3d	*tmp;

// 	norm = cyl->origin;
// 	help = create_vec3d(norm->x - ray->origin->x, norm->y - ray->origin->y, norm->z - ray->origin->z);
// 	norm = vec3d_cross(help, ray->dir);
// 	free(help);
// 	help = vec3d_cross(norm, ray->dir);
// 	free(norm);
// 	norm = help;
// 	vec3d_norm(norm);
// 	vec3d_mult(norm, cyl->d / 2);
// 	help = create_vec3d(orig->x - norm->x, orig->y - norm->y, orig->z - norm->z);
// 	tmp = create_vec3d(orig->x + norm->x, orig->y + norm->y, orig->z + norm->z);
// 	free(norm);
// 	if (ray_vec3d(ray, tmp))
// 	{
// 		free(help);
// 		return (tmp);
// 	}
// 	free(tmp);
// 	return (help);
// }

// static t_vec3d	*parallel(t_cylinder *cyl, t_ray *ray)
// {
// 	t_vec3d	*tmp;
// 	t_vec3d	*out;
// 	double	dist;

// 	vec3d_mult(cyl->norm, cyl->h);
// 	tmp = create_vec3d(cyl->origin->x + cyl->norm->x, cyl->origin->y + cyl->norm->y, cyl->origin->z + cyl->norm->z);
// 	if (cyl_ray_equal(cyl, ray))
// 	{
// 		if (vec3d_dist(tmp, ray->origin) > vec3d_dist(cyl->origin, ray->origin))
// 		{
// 			free(tmp);
// 			return (vec3d_cpy(cyl->origin));
// 		}
// 		return (tmp);
// 	}
// 	dist = ray_vec3d_dist(ray, cyl->origin);
// 	if (dist > cyl->d / 2)
// 	{
// 		free(tmp);
// 		return (NULL);
// 	}
// 	out = parallel_util(cyl, ray, tmp); //doesn´t work because 90°
// 	free(tmp);
// 	tmp = parallel_util(cyl, ray, cyl->origin);
// 	if (vec3d_dist(out, ray->origin) > vec3d_dist(tmp, ray->origin))
// 	{
// 		free(out);
// 		return (tmp);
// 	}
// 	free(tmp);
// 	return (out);
// }

// t_vec3d	*cyl_ray_inter(t_cylinder *cyl, t_ray *ray)
// {
// 	t_vec3d	*help;
// 	t_vec3d	*out;
// 	t_plane	*tmp;
// 	t_ray	*a;
// 	double	dist;

// 	if (!cyl || !ray)
// 		return (NULL);
// 	vec3d_norm(ray->dir);
// 	vec3d_norm(cyl->norm);
// 	// print_vec3d(ray->dir);
// 	// print_vec3d(cyl->norm);
// 	if (vec3d_vec3d_equal(ray->dir, cyl->norm))
// 		return (parallel(cyl, ray));
// 	tmp = create_plane(vec3d_cpy(cyl->origin), vec3d_cpy(ray->dir), 0);
// 	help = plane_ray_inter(ray, tmp);
// 	a = create_vray(vec3d_cpy(cyl->origin), vec3d_cpy(cyl->norm), 0);
// 	dist = ray_vec3d_dist(a, help);
// 	destroy_plane(tmp);
// 	destroy_ray(a);
// 	if (dist > cyl->d / 2)
// 	{
// 		free(help);
// 		return (NULL);
// 	}
// 	if (cmp_d(dist, cyl->d / 2))
// 		return (help);
// 	dist = sqrt(pow(cyl->d / 2, 2) - pow(dist, 2));
// 	printf("dist:%f\n", dist);
// 	out = is_closer(help, dist, ray);
// 	free(help);
// 	return (out);
// }