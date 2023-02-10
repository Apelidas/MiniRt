#include"../miniRT.h"


typedef struct tmp_s
{
	double	closest;
	int		color_r;
	int		color_g;
	int		color_b;
	int		id;
} tmp_t;

double  point_to_t(t_vec3d *inter, t_ray *ray)
{
    double	t;

	t = (inter->y - ray->origin->y) / ray->dir->y;
	return (t);
}

double	hit_sphere2(t_ray *ray, t_sphere *sphere, tmp_t	*i)
{
	t_vec3d	*inter;
	double	t;
	// inter = sphere_ray_inter(ray, sphere);
	// if (!inter || (inter->x == 0 && inter->y == 0 && inter->z ==0))
	// 	return (0);
	t = sphere_intersection(ray, sphere);
	// t = point_to_t(inter, ray);
	// if (t < i->closest)
	// {
	// 	i->closest = t;
	// 	i->color_r = sphere->r;
	// 	i->color_g = sphere->g;
	// 	i->color_b = sphere->b;
	// 	i->id = 1;
	// }
	// free(inter);
	(void)i;
	(void)inter;
	return (t);
}

double  hit_plane2(t_ray *ray, t_plane *plane, tmp_t	*i)
{
    t_vec3d	*inter;
    double  t;

    inter = plane_ray_inter(ray, plane);
    if (!inter)
        return (0);
    t = point_to_t(inter, ray);
	// if (t < i->closest)
	// {
	// 	i->closest = t;
	// 	i->color_r = plane->r;
	// 	i->color_g = plane->g;
	// 	i->color_b = plane->b;
	// 	i->id = 0;
	// }
	// free(inter);
	(void)i;
	return (t);
}

int color_of_node(t_objects *obj, t_data *info, t_ray *ray, double inter)
{
	if(obj->id == 0)
		return (color_calculation(info, obj, ray, obj->id, inter));
	if (obj->id == 1)
		return (color_calculation(info, obj, ray, obj->id, inter));
	if (obj->id == 2)
		return (color_calculation(info, obj, ray, obj->id, inter));
	return(0);
}


void	intersect2(t_data *info, int	pxl[2], t_ray *ray)
{
	t_objects	*tmp;
	double		closest;
	double		intr;
	tmp_t	*i;
	int color = 0;

	i = malloc(sizeof(tmp_t));
    if (!i)
		return ;
	closest = INFINITY;
	tmp = info->obj;
	while (tmp)
	{
		if (tmp->id == 0)
			intr = hit_plane2(ray, tmp->plane, i);
		if (tmp->id == 1)
			intr = hit_sphere2(ray, tmp->sphere, i);
		// else if (tmp->id == 2)
		// 	closest = hit_cylinder2(pxl, ray, tmp->cylinder, closest, info);
		if(closest > intr && intr > 1e-3)
		{
			closest = intr;
			color = color_of_node(tmp, info, ray, closest);

		}
		tmp = tmp->next;
	}
	// color = get_trgb(0, i->color_r, i->color_g, i->color_b);
	my_mlx_pixel_put(info, pxl[0], pxl[1], color);
}
