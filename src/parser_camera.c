# include"../miniRT.h"

void	parser_camera_helper(t_data *info, char *tmp, int indicator)
{
	if (indicator == 0)
		info->cam->pos->x = ft_atoi_float(tmp);
	if (indicator == 1)
		info->cam->pos->y = ft_atoi_float(tmp);
	if (indicator == 2)
		info->cam->pos->z = ft_atoi_float(tmp);
	if (indicator == 3)
		info->cam->dir->x = ft_atoi_float(tmp);
	if (indicator == 4)
		info->cam->dir->y = ft_atoi_float(tmp);
	if (indicator == 5)
		info->cam->dir->z = ft_atoi_float(tmp);
	if (indicator == 6)
		info->cam->FOV = ft_atoi_float(tmp);
}

void	validity_check_cam(t_data *info)
{
	if (info->cam->dir->x > 1 || info->cam->dir->x < -1 \
		|| info->cam->dir->y > 1 || info->cam->dir->y < -1 \
			|| info->cam->dir->z > 1 || info->cam->dir->z < -1)
		error("cam orientation vector not valid.");
	if (info->cam->FOV < 0 || info->cam->FOV > 180)
		error("cam FOV out of range.");
}

void	parser_camera(char *line, t_data *info)
{
	int		i;
	char	*tmp;
	int		indicator;

	i = skip_spaces(line) + 1;
	indicator = 0;
	if (line[i - 1] != 'C')
		error("wrong format.");
	while (line[i])
	{
		tmp = meaningful_string(line, i + skip_spaces(line + i));
		i += skip_spaces(line + i) + ft_strlen(tmp) \
			+ skip_spaces(line + i + ft_strlen(tmp));
		parser_camera_helper(info, tmp, indicator);
		indicator++;
		if (line[i] && line[i] == ',')
			i++;
		if (indicator == 7)
			break ;
	}
	validity_check_cam(info);
}
