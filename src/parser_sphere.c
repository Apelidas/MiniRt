# include"../miniRT.h"

void	validity_check_sph_free(t_objects	*sphere, char **tmp, char **tmp2)
{
	//add stuff here
	(void)sphere;
	free(tmp);
	free(tmp2);
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

void	parser_sphere(char *line, t_data	*info)
{
	t_objects	*new;
	char		**tmp;
	char		**tmp2;
	int			color[3];

	new = malloc(sizeof(t_objects));
	init_sphere_node(new);
	tmp = ft_split(line, ' ');
	tmp2 = ft_split(tmp[1], ',');
	new->sphere->origin->x = ft_atoi_float(tmp2[0]);
	new->sphere->origin->y = ft_atoi_float(tmp2[1]);
	new->sphere->origin->z = ft_atoi_float(tmp2[2]);
	// free(tmp2);
	new->sphere->d = ft_atoi_float(tmp[2]);
	if (ft_strchr(tmp[3], ','))
	{tmp2 = ft_split(tmp[3], ',');
	color[0] = ft_atoi(tmp2[0]);
	color[1] = ft_atoi(tmp2[1]);
	color[2] = ft_atoi(tmp2[2]);
	new->sphere->trgb = get_trgb(0, color[0], color[1], color[2]);}
	//to be cleaned later
	new->sphere->r = color[0];
	new->sphere->g = color[1];
	new->sphere->b = color[2];
	if (tmp[4])
		new->sphere->surface_type = ft_atoi(tmp[4]);
	lstaddback(&info->obj, new);
	validity_check_sph_free(new, tmp2, tmp);
}
