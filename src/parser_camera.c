#include"../miniRT.h"

void	validity_check_cam(t_data *info)
{
	if (vec3d_len(info->cam->dir) - 1 > 0.00001)
		error("cam orientation vector not normalized.");
	vec3d_norm(info->cam->dir);
	if (info->cam->FOV < 0 || info->cam->FOV > 180)
		error("cam FOV out of range.");
}

t_camera	*create_camera(void)
{
	t_camera	*out;

	out = malloc(sizeof(t_camera));
	if (!out)
		return (NULL);
	out->dir = malloc(sizeof(t_vec3d));
	if (!out->dir)
	{
		free(out);
		return (NULL);
	}
	out->pos = malloc(sizeof(t_vec3d));
	if (!out->pos)
	{
		free(out->dir);
		free(out);
		return (NULL);
	}
	return (out);
}

void	parser_camera(char *line, t_data *info)
{
	char	**tmp;
	char	**tmp2;

	info->cam = create_camera();
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
