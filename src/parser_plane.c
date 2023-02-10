
# include"../miniRT.h"

void	validity_check_pl_free(t_objects	*plane, char **tmp, char **tmp2)
{
	if (vec3d_len(plane->plane->norm) != 1)
		error ("plane vector is not a normal vector.");
	if (tmp2)
	{
		free(tmp2);
		tmp2 = NULL;
	}
	if (tmp)
	{
		free(tmp);
		tmp = NULL;
	}
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
	if (!new->plane)
		return ;
	new->plane->origin = malloc(sizeof(t_vec3d));
	if (!new->plane->origin)
		return ;
	new->plane->norm = malloc(sizeof(t_vec3d));
	if (!new->plane->norm)
		return ;
	new->id = 0;
	new->plane->surface_type = 1;
	new->sphere = NULL;
	new->next = NULL;
}

void	parser_plane(char *line, t_data	*info)
{
	t_objects	*new;
	char		**tmp;
	char		**tmp2;
	int			color[3];

	new = malloc (sizeof(t_objects));
	init_new_node(new);
	tmp = ft_split(line, ' ');
	tmp2 = ft_split(tmp[1], ',');
	new->plane->origin->x = ft_atoi_float(tmp2[0]);
	new->plane->origin->y = ft_atoi_float(tmp2[1]);
	new->plane->origin->z = ft_atoi_float(tmp2[2]);
	free(tmp2);
	tmp2 = ft_split(tmp[2], ',');
	new->plane->norm->x = ft_atoi_float(tmp2[0]);
	new->plane->norm->y = ft_atoi_float(tmp2[1]);
	new->plane->norm->z = ft_atoi_float(tmp2[2]);
	free(tmp2);
	tmp2 = ft_split(tmp[3], ',');
	color[0] = ft_atoi(tmp2[0]);
	color[1] = ft_atoi(tmp2[1]);
	color[2] = ft_atoi(tmp2[2]);
	new->plane->trgb = get_trgb(0, color[0], color[1], color[2]);
	new->plane->r = color[0];
	new->plane->g = color[1];
	new->plane->b = color[2];
	lstaddback(&info->obj, new);
	validity_check_pl_free(new, tmp, tmp2);
}
