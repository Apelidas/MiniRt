# include"../miniRT.h"

void	check_begining(char *s, char *line, int index)
{
	if (line[index - 2] != s[0] || line[index - 1] != s[1])
		error("wrong format.");
}

void	validity_check_cy_free(t_objects	*cylinder, char **tmp, char **tmp2)
{
	if (!is_normal_vector(cylinder->cylinder->norm))
		error("cylinder vector is not a normal vector.");
	if (tmp)
	{	
		free(tmp);
		tmp = NULL;
	}
	if (tmp2)
	{
		free(tmp2);
		tmp2 = NULL;
	}
}

void	init_cylinder_node(t_objects *new)
{
	if (!new)
		return ;
	new->cylinder = malloc(sizeof(t_cylinder));
	if (!new->cylinder)
		return ;
	new->cylinder->origin = malloc(sizeof(t_vec3d));
	if (!new->cylinder->origin)
		return ;
	new->cylinder->norm = malloc (sizeof(t_vec3d));
	if (!new->cylinder->norm)
		return ;
	new->next = NULL;
	new->id = 2;
	new->cylinder->surface_type = 1;
	// new->sphere = NULL;
	// new->plane = NULL;
}

void	parser_cylinder(char *line, t_data	*info)
{
	char		**tmp;
	char		**tmp2;
	t_objects	*new;
	int			color[3];

	new = malloc (sizeof(t_objects));
	init_cylinder_node(new);
	tmp = ft_split(line, ' ');
	tmp2 = ft_split(tmp[1], ',');
	new->cylinder->origin->x = ft_atoi_float(tmp2[0]);
	new->cylinder->origin->y = ft_atoi_float(tmp2[1]);
	new->cylinder->origin->z = ft_atoi_float(tmp2[2]);
	free(tmp2);
	tmp2 = ft_split(tmp[2], ',');
	new->cylinder->norm->x = ft_atoi_float(tmp2[0]);
	new->cylinder->norm->y = ft_atoi_float(tmp2[1]);
	new->cylinder->norm->z = ft_atoi_float(tmp2[2]);
	free(tmp2);
	new->cylinder->d = ft_atoi_float(tmp[3]);
	new->cylinder->h = ft_atoi_float(tmp[4]);
	tmp2 = ft_split(tmp[5], ',');
	color[0] = ft_atoi(tmp2[0]);
	color[1] = ft_atoi(tmp2[1]);
	color[2] = ft_atoi(tmp2[2]);
	new->cylinder->r = color[0];
	new->cylinder->g = color[1];
	new->cylinder->b = color[2];
	new->cylinder->trgb = get_trgb(0, color[0], color[1], color[2]);
	lstaddback(&(info->obj), new);
	validity_check_cy_free(new, tmp, tmp2);
}
