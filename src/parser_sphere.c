#include"../miniRT.h"

int	validity_check_sph_free(t_objects	*sphere, char **tmp, char **tmp2)
{
	(void)sphere;
	destroy_split(tmp);
	destroy_split(tmp2);
	return (1);
}

void	init_sphere_node(t_objects	*new)
{
	if (!new)
		return ;
	new->sphere = malloc(sizeof(t_sphere));
	if (!new->sphere)
		return ;
	new->sphere->origin = malloc(sizeof(t_vec3d));
	if (!new->sphere->origin)
		return ;
	new->id = 1;
	new->sphere->surface_type = 1;
	new->plane = NULL;
	new->next = NULL;
}

static int	sphere_norm(char **tmp, t_objects *new)
{
	char		**tmp2;
	int			color[3];

	tmp2 = ft_split(tmp[3], ',');
	if (!tmp2 || split_len(tmp2) != 3)
		return (error_int("missing sphere info"));
	color[0] = ft_atoi(tmp2[0]);
	color[1] = ft_atoi(tmp2[1]);
	color[2] = ft_atoi(tmp2[2]);
	new->sphere->trgb = get_trgb(0, color[0], color[1], color[2]);
	new->sphere->r = color[0];
	new->sphere->g = color[1];
	new->sphere->b = color[2];
	if (tmp[4])
		new->sphere->surface_type = ft_atoi(tmp[4]);
	else
		new->sphere->surface_type = 1;
	return (1);
}

int	parser_sphere(char *line, t_data	*info)
{
	t_objects	*new;
	char		**tmp;
	char		**tmp2;

	new = malloc(sizeof(t_objects));
	init_sphere_node(new);
	lstaddback(&info->obj, new);
	tmp = ft_split(line, ' ');
	if (!tmp)
		return (error_int("missing sphere info"));
	tmp2 = ft_split(tmp[1], ',');
	if (!tmp2 || split_len(tmp2) != 3)
		return (error_int("missing sphere info"));
	new->sphere->origin->x = ft_atoi_float(tmp2[0]);
	new->sphere->origin->y = ft_atoi_float(tmp2[1]);
	new->sphere->origin->z = ft_atoi_float(tmp2[2]);
	destroy_split(tmp2);
	if (!tmp[2])
		return (error_int("missing sphere info"));
	new->sphere->d = ft_atoi_float(tmp[2]);
	if (!sphere_norm(tmp, new))
		return (0);
	return (validity_check_sph_free(new, tmp2, tmp));
}
