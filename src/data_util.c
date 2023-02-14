#include"../miniRT.h"

void	window_init(t_data *info)
{
	info->mlx = malloc(sizeof(t_mlx));
	if (!info->mlx)
		return ;
	info->mlx->mlx = mlx_init();
	if (!info->mlx->mlx)
		return ;
	info->mlx->img = mlx_new_image(info->mlx->mlx, SCREEN_WIDTH, SCREEN_HIGHT);
	if (!info->mlx->img)
		return ;
	info->mlx->win = mlx_new_window(info->mlx->mlx, SCREEN_WIDTH, \
		SCREEN_HIGHT, "miniRT");
	if (!info->mlx->win)
		return ;
	info->mlx->addr = mlx_get_data_addr(info->mlx->img, &info->mlx->bpp, \
		&info->mlx->l_length, &info->mlx->endian);
}

void	data_init(t_data *info)
{
	info->amb = malloc(sizeof(t_amb));
	if (!info->amb)
		return ;
	info->amb->trgb = 8421504;
	info->amb->ratio = 0.2;
	info->cam = NULL;
	info->light = NULL;
	info->obj = NULL;
	window_init(info);
}

void	destroy_data(t_data *info)
{
	t_objects	*tmp;
	t_objects	*next;
	t_light		*help;
	t_light		*help2;

	if (!info)
		return ;
	tmp = info->obj;
	while (tmp)
	{
		if (tmp->id == 0)
			destroy_plane(tmp->plane);
		if (tmp->id == 1)
			destroy_sphere(tmp->sphere);
		if (tmp->id == 2)
			destroy_cylinder(tmp->cylinder);
		next = tmp;
		tmp = tmp->next;
		free(next);
	}
	help = info->light;
	while (help)
	{
		help2 = help;
		help = help->next;
		free(help2);
	}
	free(info->amb);
	free(info->cam->pos);
	free(info->cam->dir);
	free(info->cam);
	destroy_mlx(info->mlx);
	free(info);
}