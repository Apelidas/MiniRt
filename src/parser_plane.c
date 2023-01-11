
# include"../miniRT.h"

void	parse_plane_helper(t_plane	*plane, char *tmp, int indicator)
{
	plane->origin = malloc(sizeof(t_vec3d));
	plane->norm = malloc(sizeof(t_vec3d));
	plane->trgb = malloc (sizeof(t_color));
	if (indicator == 0)
		{plane->origin->x = ft_atoi_float(tmp);
			printf("lalalaFuuuu%f\n", plane->origin->x);}

	if (indicator == 1)
		plane->origin->y =  ft_atoi_float(tmp);
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
	{
		plane->trgb->b = ft_atoi(tmp);
		printf("uuuu%d\n", plane->trgb->b);
	}
}

int	parser_plane(char *line, t_data	*info, int  index)
{
	int		i;
	t_plane	*plane;
	char	*tmp;
	int		indicator;

	i = 0;
	plane = malloc(sizeof(t_plane));
	i = skip_spaces(line) + 2;
	indicator = 0;
	if (line[i - 2] != 'p' || line[i - 1] != 'l')
		error("plane wrong format.");
	while (line[i])
	{
		tmp = meaningful_string(line, i + skip_spaces(line + i));
		i += skip_spaces(line + i) + ft_strlen(tmp) \
			+ skip_spaces(line + i + ft_strlen(tmp));
		parse_plane_helper(plane, tmp, indicator);
		indicator++;
		if (line[i] && line[i] == ',')
			i++;
		if (indicator == 9)
			break ;
	}
	printf("Fuuuu%f\n", plane->origin->x);
	info->obj[index].plane = plane;
	info->obj[index].id = 0;
	printf("FFuuuu%f\n", info->obj[0].plane->origin->x);
	return (index + 1);
}
