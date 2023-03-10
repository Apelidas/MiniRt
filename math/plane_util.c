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
	double	tmp2;
	t_vec3d	*tmp;
	t_vec3d	*inter;

	if (!ray || !plane)
		return (NULL);
	inter = create_vec3d(0, 0, 0);
	if (!inter)
		return (NULL);
	vec3d_norm(plane->norm);
	tmp = vec3d_sub(plane->origin, ray->origin);
	tmp2 = vec3d_dot(ray->dir, plane->norm);
	t = vec3d_dot(tmp, plane->norm);
	t = t / tmp2;
	free(tmp);
	if (t <= 0)
	{
		free(inter);
		return (NULL);
	}
	inter->x = ray->origin->x + t * ray->dir->x;
	inter->y = ray->origin->y + t * ray->dir->y;
	inter->z = ray->origin->z + t * ray->dir->z;
	return (inter);
}

int	plane_cam_light(t_data *info, t_plane *plane)
{
	t_ray	*cam;
	t_ray	*light;
	t_vec3d	*cinter;
	t_vec3d	*linter;
	int		out;

	out = 1;
	cam = create_vray(info->cam->pos, plane->norm, 0);
	light = create_vray(info->light->pos, plane->norm, 0);
	cinter = plane_ray_inter(cam, plane);
	linter = plane_ray_inter(light, plane);
	if ((cinter && !linter) || (!cinter && linter))
		out = 0;
	free(linter);
	free(cinter);
	free(light);
	free(cam);
	return (out);
}
