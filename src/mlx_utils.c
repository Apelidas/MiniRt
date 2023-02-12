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
