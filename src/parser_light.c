#include"../miniRT.h"

int	validity_check_light(t_data *info)
{
	if (info->light->bright > 1 || info->light->bright < 0)
		return (error_int("invalid brightness ratio."));
	return (1);
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

static int	light_norm(char **tmp, t_light *new)
{
	char	**tmp2;
	int		color[3];

	if (!tmp[2])
		return (error_int("missing amb info"));
	new->bright = ft_atoi_float(tmp[2]);
	if (tmp[3] && ft_strchr(tmp[3], ','))
	{
		tmp2 = ft_split(tmp[3], ',');
		if (!tmp2 || split_len(tmp2) != 3)
			return (error_int("missing amb info"));
		color[0] = ft_atoi(tmp2[0]);
		color[1] = ft_atoi(tmp2[1]);
		color[2] = ft_atoi(tmp2[2]);
		new->trgb = get_trgb(0, color[0], color[1], color[2]);
		new->r = color[0];
		new->g = color[1];
		new->b = color[2];
		destroy_split(tmp2);
	}
	return (1);
}

int	parser_light(char **tmp, t_data *info)
{
	char	**tmp2;
	t_light	*new;

	new = malloc(sizeof(t_light));
	init_light_node(new);
	lstaddback_light(&(info->light), new);
	if (!tmp)
		return (error_int("missing amb info"));
	tmp2 = ft_split(tmp[1], ',');
	if (!tmp2 || split_len(tmp2) != 3)
		return (error_int("missing amb info"));
	new->pos->x = ft_atoi_float(tmp2[0]);
	new->pos->y = ft_atoi_float(tmp2[1]);
	new->pos->z = ft_atoi_float(tmp2[2]);
	destroy_split(tmp2);
	light_norm(tmp, new);
	return (validity_check_light(info));
}
