#include"../miniRT.h"


double  point_to_t(t_vec3d *inter, t_ray *ray)
{
    double	t;

	t = (inter->y - ray->origin->y) / ray->dir->y;
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
    double  t;

    t = plane_intersection(ray->dir, info->cam->pos, plane->norm, plane->origin);

    // if (!t)
    //     return (0);
    // t = point_to_t(inter, ray);
	// free(inter);
	return (t);
}


void	intersect2(t_data *info, int	pxl[2], t_ray *ray)
{
	t_objects	*tmp;
	double		closest;
	double		intr;
	int color = 0;

	closest = INFINITY;
	tmp = info->obj;
	while (tmp)
	{
		if (tmp->id == 0)
			intr = hit_plane2(ray, tmp->plane, info);
		if (tmp->id == 1)
			intr = hit_sphere2(ray, tmp->sphere);
		// else if (tmp->id == 2)
		// 	intr = hit_cylinder2(pxl, ray, tmp->cylinder, closest, info);
		if(closest > intr && intr > 1e-4)
		{
			closest = intr;
			color = color_calculation(info, tmp, ray, intr);
		}
		tmp = tmp->next;
	}
	my_mlx_pixel_put(info, pxl[0], pxl[1], color);
}
