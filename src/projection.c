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

t_ray	*make_ray(t_data *info, double x, double y)
{
	t_vec3d	*tmp;
	t_vec3d	*right;
	t_vec3d	*up;
	t_vec3d	*up_guide;
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	up_guide = create_vec3d(0, 1, 0);
	vec3d_norm(info->cam->dir);
	right = vec3d_cross(info->cam->dir, up_guide);
	vec3d_norm(right);
	up = vec3d_cross(right, info->cam->dir);
	vec3d_norm(up);
	vec3d_mult(right, x);
	vec3d_mult(up, y);
	tmp = vec3d_plus(right, up);
	ray = create_vray(vec3d_cpy(info->cam->pos),
			vec3d_plus(tmp, info->cam->dir), 0);
	free(tmp);
	free(up);
	free(right);
	free(up_guide);
	return (ray);
}

void	convert_pixels(int x_pxl, int y_pxl, t_data *info, double scrn_xy[2])
{
	scrn_xy[0] = ((2 * (double)x_pxl + 0.5) \
		/ (double)SCREEN_WIDTH - 1) * tan((info->cam->FOV * M_PI / 180) / 2) \
			* ASPECT_RATIO;
	scrn_xy[1] = (1 - 2 * ((double)y_pxl + 0.5) \
		/ (double)SCREEN_HIGHT) * tan((info->cam->FOV * M_PI / 180) / 2);
}

void	projection(t_data *info)
{
	int			pxl_xy[2];
	double		scrn_xy[2];
	t_ray		*ray;

	pxl_xy[0] = 0;
	while (pxl_xy[0] <= SCREEN_WIDTH)
	{
		pxl_xy[1] = 0;
		while (pxl_xy[1] <= SCREEN_HIGHT)
		{
			convert_pixels(pxl_xy[0], pxl_xy[1], info, scrn_xy);
			ray = make_ray(info, scrn_xy[0], scrn_xy[1]);
			intersect2(info, pxl_xy, ray);
			destroy_ray(ray);
			pxl_xy[1]++;
		}
		pxl_xy[0]++;
	}
}
