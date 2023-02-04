#include"../miniRT.h"

void	validity_check_light(t_data *info)
{
	if (info->light->bright > 1 || info->light->bright < 0)
		error ("invalid brightness ratio.");
}

void	init_light_node(t_light *new)
{
	if (!new)
		return ;
	new->pos = malloc(sizeof(t_vec3d));
	if (!new->pos)
		return ;
	new->next = NULL;
}

void	lstaddback_light(t_light **lst, t_light *new)
{
	t_light	*tmp;

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

void	parser_light(char *line, t_data *info)
{
	char	**tmp;
	char	**tmp2;
	int		color[3];
	t_light	*new;

	new = malloc(sizeof(t_light));
	init_light_node(new);
	tmp = ft_split(line, ' ');
	tmp2 = ft_split(tmp[1], ',');
	new->pos->x = ft_atoi_float(tmp2[0]);
	new->pos->y = ft_atoi_float(tmp2[1]);
	new->pos->z = ft_atoi_float(tmp2[2]);
	free(tmp2);
	new->bright = ft_atoi_float(tmp[2]);
	if (ft_strchr(tmp[3], ','))
	{
		tmp2 = ft_split(tmp[3], ',');
		color[0] = ft_atoi(tmp2[0]);
		color[1] = ft_atoi(tmp2[1]);
		color[2] = ft_atoi(tmp2[2]);
		new->trgb = get_trgb(0, color[0], color[1], color[2]);
		free(tmp2);
	}
	free(tmp);
	lstaddback_light(&info->light, new);
	validity_check_light(info);
}
