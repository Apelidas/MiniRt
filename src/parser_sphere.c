# include"../miniRT.h"

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
	new->sphere->trgb = malloc(sizeof(t_color));
	if (new->sphere->trgb)
		return ;
	new->id = 1;
	new->plane = NULL;
	new->next = NULL;
}

void	parse_sphere_helper(t_sphere	*sphere, char *tmp, int indicator)
{
	if (indicator == 0)
		sphere->origin->x = ft_atoi_float(tmp);
	if (indicator == 1)
		sphere->origin->y = ft_atoi_float(tmp);
	if (indicator == 2)
		sphere->origin->z = ft_atoi_float(tmp);
	if (indicator == 3)
		sphere->d = ft_atoi_float(tmp);
	if (indicator == 4)
		sphere->trgb->r = ft_atoi(tmp);
	if (indicator == 5)
		sphere->trgb->g = ft_atoi(tmp);
	if (indicator == 6)
		sphere->trgb->b = ft_atoi(tmp);
}

void	parser_sphere(char *line, t_data	*info)
{
	t_objects	*new;
	int			i;
	int			indicator;
	char		*tmp;

	new = malloc(sizeof(t_objects));
	init_sphere_node(new);
	i = skip_spaces(line) + 2;
	indicator = 0;
	if (line[i - 2] != 's' || line[i - 1] != 'p')
		error("sphere wrong format.");
	while (line[i])
	{
		tmp = meaningful_string(line, i + skip_spaces(line + i));
		i += skip_spaces(line + i) + ft_strlen(tmp) \
			+ skip_spaces(line + i + ft_strlen(tmp));
		parse_sphere_helper(new->sphere, tmp, indicator);
		indicator++;
		if (line[i] && line[i] == ',')
			i++;
		if (indicator == 7)
			break ;
	}
	lstaddback(&info->obj, new); // why doesnr this added correctly? donno...
	// printf("sphere data %f  %f %f", info->obj->sphere->origin->x, info->obj->sphere->origin->y, info->obj->sphere->origin->z);
}
