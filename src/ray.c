#include "../miniRT.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < SCREEN_WIDTH && y < SCREEN_HIGHT && x > 0 && y > 0)
	{
		dst = data->mlx->addr + (y * data->mlx->l_length
				+ x * (data->mlx->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	*make_ray_camera(t_vec3d	*screen_point, t_data *info)
{
	t_ray	*ray;

	ray = malloc (sizeof(t_ray));
	if (!ray)
		return (NULL);
	ray->origin = info->cam->pos;
	ray->dir = screen_point;
	return (ray);
}
