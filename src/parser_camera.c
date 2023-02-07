# include"../miniRT.h"

void	validity_check_cam(t_data *info)
{
	vec3d_norm(info->cam->dir);
	// if (vec3d_len(info->cam->dir) != 1)
	// 	error("cam orientation vector not normalized.");
	if (info->cam->FOV < 0 || info->cam->FOV > 180)
		error("cam FOV out of range.");
}

void	parser_camera(char *line, t_data *info)
{
	char	**tmp;
	char	**tmp2;

	tmp = ft_split(line, ' ');
	tmp2 = ft_split(tmp[1], ',');
	info->cam->pos->x = ft_atoi_float(tmp2[0]);
	info->cam->pos->y = ft_atoi_float(tmp2[1]);
	info->cam->pos->z = ft_atoi_float(tmp2[2]);
	free(tmp2);
	tmp2 = ft_split(tmp[2], ',');
	info->cam->dir->x = ft_atoi_float(tmp2[0]);
	info->cam->dir->y = ft_atoi_float(tmp2[1]);
	info->cam->dir->z = ft_atoi_float(tmp2[2]);
	info->cam->FOV = ft_atoi(tmp[3]);
	free(tmp2);
	validity_check_cam(info);
	free(tmp);
}
