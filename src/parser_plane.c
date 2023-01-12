
# include"../miniRT.h"

void	validity_check_pl(t_objects	*plane, char *tmp)
{
	if (!is_normal_vector(plane->plane->norm))
		error ("plane vector is not a normal vector.");
	if (!is_color(plane->plane->trgb))
		error("plane colors out of range.");
	free(tmp);
}

void	lstaddback(t_objects **lst, t_objects *new)
{
	t_objects	*tmp;

	tmp = *lst;
	if (tmp == NULL)
		*lst = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	init_new_node(t_objects	*new)
{
	if (!new)
		return ;
	new->plane = malloc(sizeof(t_plane));
	new->plane->origin = malloc(sizeof(t_vec3d));
	new->plane->norm = malloc(sizeof(t_vec3d));
	new->plane->trgb = malloc (sizeof(t_color));
	new->id = 0;
	new->sphere = NULL;
	new->next = NULL;
}

void	parse_plane_helper(t_plane	*plane, char *tmp, int indicator)
{
	if (indicator == 0)
		plane->origin->x = ft_atoi_float(tmp);
	if (indicator == 1)
		plane->origin->y = ft_atoi_float(tmp);
	if (indicator == 2)
		plane->origin->z = ft_atoi_float(tmp);
	if (indicator == 3)
		plane->norm->x = ft_atoi_float(tmp);
	if (indicator == 4)
		plane->norm->y = ft_atoi_float(tmp);
	if (indicator == 5)
		plane->norm->z = ft_atoi_float(tmp);
	if (indicator == 6)
		plane->trgb->r = ft_atoi(tmp);
	if (indicator == 7)
		plane->trgb->g = ft_atoi(tmp);
	if (indicator == 8)
		plane->trgb->b = ft_atoi(tmp);
}

void	parser_plane(char *line, t_data	*info)
{
	int			i;
	char		*tmp;
	int			indicator;
	t_objects	*new;

	i = 0;
	new = malloc (sizeof(t_objects));
	init_new_node(new);
	i = skip_spaces(line) + 2;
	indicator = 0;
	check_begining("pl", line, i);
	while (line[i])
	{
		tmp = meaningful_string(line, i + skip_spaces(line + i));
		i += skip_spaces(line + i) + ft_strlen(tmp) \
			+ skip_spaces(line + i + ft_strlen(tmp));
		parse_plane_helper(new->plane, tmp, indicator);
		indicator++;
		if (line[i] && line[i] == ',')
			i++;
		if (indicator == 9)
			break ;
	}
	(void)info;
	// lstaddback(&info->obj, new);
	validity_check_pl(new, tmp);
}
