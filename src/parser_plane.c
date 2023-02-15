
#include"../miniRT.h"

void	validity_check_pl_free(t_objects	*plane, char **tmp, char **tmp2)
{
	if (tmp2)
	{
		destroy_split(tmp2);
		tmp2 = NULL;
	}
	if (tmp)
	{
		destroy_split(tmp);
		tmp = NULL;
	}
	if (!cmp_d(vec3d_len(plane->plane->norm), 1))
		error("Plane norm is not norminalized");
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

static void	plane_norm(char **tmp, t_objects *new)
{
	char		**tmp2;
	int			color[3];

	tmp2 = ft_split(tmp[2], ',');
	if (!tmp2 || split_len(tmp2) != 3)
		error("missing plane info");
	new->plane->norm->x = ft_atoi_float(tmp2[0]);
	new->plane->norm->y = ft_atoi_float(tmp2[1]);
	new->plane->norm->z = ft_atoi_float(tmp2[2]);
	destroy_split(tmp2);
	tmp2 = ft_split(tmp[3], ',');
	if (!tmp2 || split_len(tmp2) != 3)
		error("missing plane info");
	color[0] = ft_atoi(tmp2[0]);
	color[1] = ft_atoi(tmp2[1]);
	color[2] = ft_atoi(tmp2[2]);
	new->plane->trgb = get_trgb(0, color[0], color[1], color[2]);
	new->plane->r = color[0];
	new->plane->g = color[1];
	new->plane->b = color[2];
}

void	parser_plane(char *line, t_data	*info)
{
	t_objects	*new;
	char		**tmp;
	char		**tmp2;

	new = malloc (sizeof(t_objects));
	init_new_node(new);
	tmp = ft_split(line, ' ');
	if (!tmp)
		error("missing plane info");
	tmp2 = ft_split(tmp[1], ',');
	if (!tmp2 || split_len(tmp2) != 3)
		error("missing plane info");
	new->plane->origin->x = ft_atoi_float(tmp2[0]);
	new->plane->origin->y = ft_atoi_float(tmp2[1]);
	new->plane->origin->z = ft_atoi_float(tmp2[2]);
	destroy_split(tmp2);
	plane_norm(tmp, new);
	if (tmp[4])
		new->plane->surface_type = ft_atoi(tmp[4]);
	else
		new->plane->surface_type = 1;
	lstaddback(&info->obj, new);
	validity_check_pl_free(new, tmp, tmp2);
}
