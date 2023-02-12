#include "../miniRT.h"

int	key_hook(int key_code, t_data *info)
{
	if (key_code == 53 || key_code == 8)
	{
		if (info->mlx->mlx && info->mlx->img)
			mlx_destroy_image(info->mlx->mlx, info->mlx->img);
		// if ( info->mlx->mlx && info->mlx->win) check this later
		// 	mlx_destroy_window(info->mlx->mlx, info->mlx->win);
		exit(1);
	}
	if (key_code == 13)
		camera_move(info, 1, 0);
	else if (key_code == 0)
		camera_move(info, 0, -1);
	else if (key_code == 1)
		camera_move(info, -1, 0);
	else if (key_code == 2)
		camera_move(info, 0, 1);
	else if (key_code == 126)
		camera_dir_move(info, 1, 0);
	else if (key_code == 123)
		camera_dir_move(info, 0, 1);
	else if (key_code == 125)
		camera_dir_move(info, -1, 0);
	else if (key_code == 124)
		camera_dir_move(info, 0, -1);
	mlx_destroy_image(info->mlx->mlx, info->mlx->img);
	info->mlx->img = NULL;
	info->mlx->img = mlx_new_image(info->mlx->mlx, SCREEN_WIDTH, SCREEN_HIGHT);
	projection(info);
	print_vec3d(info->cam->pos);
	mlx_put_image_to_window(info->mlx->mlx, info->mlx->win, info->mlx->img, 0, 0);
	return (0);
}

int	close_x(t_data	*info)
{
	if (info->mlx->img && info->mlx->mlx)
		mlx_destroy_image(info->mlx->mlx, info->mlx->img);
	exit(0);
}

void	destroy_mlx(t_mlx *mlx)
{
	if (!mlx)
		return ;
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	free(mlx);
}
