#include"../miniRT.h"

double	point_to_t(t_vec3d *inter, t_ray *ray)
{
	double	t;

	t = -1;
	if (ray->dir->x)
		t = (inter->x - ray->origin->x) / ray->dir->x;
	else if (ray->dir->y)
		t = (inter->y - ray->origin->y) / ray->dir->y;
	else if (ray->dir->z)
		t = (inter->z - ray->origin->z) / ray->dir->z;
	return (t);
}

double	hit_sphere2(t_ray *ray, t_sphere *sphere)
{
	t_vec3d	*inter;
	double	t;
	// inter = sphere_ray_inter(ray, sphere);
	// if (!inter || (inter->x == 0 && inter->y == 0 && inter->z ==0))
	// 	return (0);
	// t = point_to_t(inter, ray);
	t = sphere_intersection(ray, sphere);
	if (t == -1)
		return (0);
	(void)inter;
	return (t);
}

double  hit_plane2(t_ray *ray, t_plane *plane, t_data *info)
{
	double	t;
	t_vec3d	*inter;

	(void)info;
    inter = plane_ray_inter(ray, plane);
	if (!inter)
		return (-1);
	t = point_to_t(inter, ray);
	if (t <= 0)
		return (-1);
	return (t);
}

double	hit_cylinder2(t_ray *ray, t_cyl *cyl)
{
	t_vec3d	*inter;
	double	t;

	inter = cyl_ray_inter(cyl, ray);
	if (!inter)
		return (-1);
	vec3d_norm(cyl->norm);
	t = point_to_t(inter, ray);
	if (t <= 0)
		return (-1);
	return (t);
}

void	intersect2(t_data *info, int pxl[2], t_ray *ray)
{
	t_objects	*tmp;
	double		closest;
	double		intr;
	int			color;

	closest = INFINITY;
	tmp = info->obj;
	color = 0;
	while (tmp)
	{
		if (tmp->id == 0)
			intr = plane_intersection(ray, info, tmp->plane);
		if (tmp->id == 1)
			intr = hit_sphere2(ray, tmp->sphere);
		if (tmp->id == 2)
			intr = hit_cylinder2(ray, tmp->cylinder);
				// if (tmp->cylinder->b == 128)
				// {
				// 	if(closest > intr && intr > 0)
				// 		printf("test this shit%f %f |", closest, intr);
				// }}
		if (closest > intr && intr > 1e-4)
		{
			closest = intr;
			color = color_calculation(info, tmp, ray, intr);
		}
		tmp = tmp->next;
	}
	my_mlx_pixel_put(info, pxl[0], pxl[1], color);
}
