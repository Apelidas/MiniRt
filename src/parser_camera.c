#include"../miniRT.h"

int	validity_check_cam(t_data *info)
{
	if (!cmp_d(vec3d_len(info->cam->dir), 1))
		return (error_int("cam orientation vector not normalized."));
	vec3d_norm(info->cam->dir);
	if (info->cam->fov < 0 || info->cam->fov > 180)
		return (error_int("cam fov out of range."));
	return (1);
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

static void	parser_norm(char **tmp2, t_vec3d *dir)
{
	dir->x = ft_atoi_float(tmp2[0]);
	dir->y = ft_atoi_float(tmp2[1]);
	dir->z = ft_atoi_float(tmp2[2]);
}

int	parser_camera(char **tmp, t_data *info)
{
	char	**tmp2;

	if (info->cam)
		return (error_int("Too many cameras"));
	info->cam = create_camera();
	if (!tmp || split_len(tmp) < 4)
		return (error_int("missing camera info"));
	tmp2 = ft_split(tmp[1], ',');
	if (!tmp2 || split_len(tmp2) < 3)
		return (error_int("missing camera info"));
	parser_norm(tmp2, info->cam->pos);
	destroy_split(tmp2);
	tmp2 = ft_split(tmp[2], ',');
	if (!tmp2 || split_len(tmp2) < 3)
		return (error_int("missing camera info"));
	parser_norm(tmp2, info->cam->dir);
	info->cam->fov = ft_atoi(tmp[3]);
	destroy_split(tmp2);
	return (validity_check_cam(info));
}
