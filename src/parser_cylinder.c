#include"../miniRT.h"

int	validity_check_cy_free(t_objects	*cylinder, char **tmp, char **tmp2)
{
	if (!is_normal_vector(cylinder->cylinder->norm))
		return (error_int("cylinder vector is not a normal vector."));
	if (tmp)
	{	
		destroy_split(tmp);
		tmp = NULL;
	}
	if (tmp2)
	{
		destroy_split(tmp2);
		tmp2 = NULL;
	}
	return (1);
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
}

static int	pcylinder_norm(char **tmp, t_objects *new)
{
	char	**tmp2;

	tmp2 = ft_split(tmp[1], ',');
	if (!tmp2 || split_len(tmp2) != 3)
		return (error_int("missing cylinder info"));
	new->cylinder->origin->x = ft_atoi_float(tmp2[0]);
	new->cylinder->origin->y = ft_atoi_float(tmp2[1]);
	new->cylinder->origin->z = ft_atoi_float(tmp2[2]);
	destroy_split(tmp2);
	tmp2 = ft_split(tmp[2], ',');
	if (!tmp2 || split_len(tmp2) != 3)
		return (error_int("missing cylinder info"));
	new->cylinder->norm->x = ft_atoi_float(tmp2[0]);
	new->cylinder->norm->y = ft_atoi_float(tmp2[1]);
	new->cylinder->norm->z = ft_atoi_float(tmp2[2]);
	destroy_split(tmp2);
	new->cylinder->d = ft_atoi_float(tmp[3]);
	new->cylinder->h = ft_atoi_float(tmp[4]);
	return (1);
}

static void	parser_norm(t_cylinder *cylinder, char **tmp2)
{
	int	color[3];

	color[0] = ft_atoi(tmp2[0]);
	color[1] = ft_atoi(tmp2[1]);
	color[2] = ft_atoi(tmp2[2]);
	cylinder->r = color[0];
	cylinder->g = color[1];
	cylinder->b = color[2];
	cylinder->trgb = get_trgb(0, color[0], color[1], color[2]);
}

int	parser_cylinder(char *line, t_data	*info)
{
	char		**tmp;
	char		**tmp2;
	t_objects	*new;

	new = malloc (sizeof(t_objects));
	init_cylinder_node(new);
	lstaddback(&(info->obj), new);
	tmp = ft_split(line, ' ');
	if (!tmp)
		return (error_int("missing cylinder info"));
	pcylinder_norm(tmp, new);
	tmp2 = ft_split(tmp[5], ',');
	if (!tmp2 || split_len(tmp2) != 3)
		return (error_int("missing cylinder info"));
	parser_norm(new->cylinder, tmp2);
	if (tmp[6])
		new->cylinder->surface_type = ft_atoi(tmp[6]);
	else
		new->cylinder->surface_type = 1;
	return (validity_check_cy_free(new, tmp, tmp2));
}
