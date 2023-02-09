#include "operations.h"

/*
checks if a ray and a plane have a point of intesrsection
*/
int	plane_ray_touch(t_ray *ray, t_plane	*plane)
{
	double	dot;
	double	angle;
	t_vec3d	*help;

	vec3d_norm(ray->dir);
	vec3d_norm(plane->norm);
	dot = vec3d_dot(ray->dir, plane->norm);
	help = create_vec3d(plane->origin->x - ray->origin->x,
			plane->origin->y - ray->origin->y,
			plane->origin->z - ray->origin->z);
	angle = vec3d_angle(help, ray->dir);
	free(help);
	if (cmp_d(dot, 0))
		return (0);
	if (angle > 90)
		return (0);
	return (1);
}


t_vec3d	*plane_ray_inter(t_ray *ray, t_plane *plane)
{
	double	t;
	t_vec3d	*tmp;
	t_vec3d	*inter;


	if (!ray || !plane)
		return (NULL);
	inter = create_vec3d(0, 0, 0);
	if (!inter)
		return (NULL);
	tmp = vec3d_sub(ray->origin, plane->origin);
	t = vec3d_dot(tmp, plane->norm);
	t = t / vec3d_dot(ray->dir, plane->norm);
	free(tmp);
	if (t >= 0)
	{
		free(inter);
		return (NULL);
	}
	inter->x = ray->origin->x + t * ray->dir->x;
	inter->y = ray->origin->y + t * ray->dir->y;
	inter->z = ray->origin->z + t * ray->dir->z;
	return (inter);
}

t_ray	*plane_reflect(t_ray *ray_in, t_plane *plane, t_vec3d *point)
{
	t_ray	*out;
	t_vec3d	*dir;

	// printf("inter:\n");
	// print_vec3d(point);
	// printf("input_ray:\n");
	// print_vec3d(ray_in->dir);
	vec3d_norm(plane->norm);
	dir = vec3d_cpy(plane->norm);
	vec3d_mult(dir, 2 * vec3d_dot(dir, ray_in->dir));
	out = create_vray(vec3d_cpy(point), vec3d_sub(ray_in->dir, dir), 0);
	free(dir);
	// printf("output_ray:\n");
	// print_vec3d(out->dir);
	// printf("angle_in: %f\nanlge_ou: %f\n", vec3d_angle(ray_in->dir, plane->norm), vec3d_angle(out->dir, plane->norm));
	return (out);
}