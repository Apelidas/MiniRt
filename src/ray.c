# include "../miniRT.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < SCREEN_WIDTH && y < SCREEN_HIGHT && x > 0 && y > 0)
	{
		dst = data->mlx->addr + (y * data->mlx->l_length
				+ x * (data->mlx->bpp / 8));
		*(unsigned int *)dst = color;
		// (void)color;
	}
}

void	*make_ray_camera(t_vec3d	*screen_point, t_data *info)
{
	t_ray	*ray;

	ray = malloc (sizeof(t_ray));
	if (!ray)
		return (NULL) ;
	ray->origin = info->cam->pos;
	ray->dir = screen_point;
	// printf("ray is %f %f %f\n", ray->dir->x, ray->dir->y, ray->dir->z);
	return (ray);
}

// void	ray_cast(t_ray *ray, t_data	*info, int px, int py)
// {
// 	t_objects	*tmp;
// 	t_vec3d		*intersection;

// 	tmp = info->obj;
// 	while (tmp)
// 	{
// 		if (tmp->id == 0)
// 		{
// 			if (plane_ray_touch(ray, tmp->plane))
// 			{
// 				intersection = plane_ray_inter(ray, tmp->plane);
// 				my_mlx_pixel_put(info, px, py, 0);
// 			}
// 		}
// 		tmp = tmp->next;
// 	}
// }
