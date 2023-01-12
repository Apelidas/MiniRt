# include"../miniRT.h"

void	check_begining(char *s, char *line, int index)
{
	if (line[index - 2] != s[0] || line[index - 1] != s[1])
		error("wrong format.");
}

void	validity_check_cy(t_objects	*cylinder, char *tmp)
{
	if (!is_normal_vector(cylinder->cylinder->norm))
		error("cylinder vector is not a normal vector.");
	free(tmp);
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
	// new->sphere = NULL;
	// new->plane = NULL;
}

void	parse_cylinder_helper(t_cylinder	*cylinder, char *tmp, int indicator)
{
	int	color[2];

	if (indicator == 0)
		cylinder->origin->x = ft_atoi_float(tmp);
	if (indicator == 1)
		cylinder->origin->y = ft_atoi_float(tmp);
	if (indicator == 2)
		cylinder->origin->z = ft_atoi_float(tmp);
	if (indicator == 3)
		cylinder->norm->x = ft_atoi_float(tmp);
	if (indicator == 4)
		cylinder->norm->y = ft_atoi_float(tmp);
	if (indicator == 5)
		cylinder->norm->z = ft_atoi_float(tmp);
	if (indicator == 6)
		cylinder->d = ft_atoi_float(tmp);
	if (indicator == 7)
		cylinder->h = ft_atoi_float(tmp);
	if (indicator == 8)
		color[0] = ft_atoi(tmp);
	if (indicator == 9)
		color[1] = ft_atoi(tmp);
	if (indicator == 10)
		cylinder->trgb = get_trgb(0, color[0], color[1], ft_atoi(tmp));
	if (indicator == 10)
		is_color(color[0], color[1], ft_atoi(tmp));
}

void	parser_cylinder(char *line, t_data	*info)
{
	int			i;
	char		*tmp;
	int			indicator;
	t_objects	*new;

	i = 0;
	new = malloc (sizeof(t_objects));
	init_cylinder_node(new);
	i = skip_spaces(line) + 2;
	indicator = 0;
	check_begining("cy", line, i);
	while (line[i])
	{
		tmp = meaningful_string(line, i + skip_spaces(line + i));
		i += skip_spaces(line + i) + ft_strlen(tmp) \
			+ skip_spaces(line + i + ft_strlen(tmp));
		parse_cylinder_helper(new->cylinder, tmp, indicator);
		indicator++;
		if (line[i] && line[i] == ',')
			i++;
		if (indicator == 11)
			break ;
	}
	(void)info;
	// lstaddback(&info->obj, new);
	validity_check_cy(new, tmp);
	printf("cylinder origin %f %f %f", new->cylinder->origin->x, new->cylinder->origin->y, new->cylinder->origin->z);
	printf("\ncylinder normal %f %f %f", new->cylinder->norm->x, new->cylinder->norm->y, new->cylinder->norm->z);
	printf("\nd %f h %f", new->cylinder->d, new->cylinder->h);
	printf("cylinder color %d\n", new->cylinder->trgb);
}
