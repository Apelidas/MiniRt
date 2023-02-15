#include"../miniRT.h"

double	ft_atoi_float(char *s)
{
	int		i;
	int		md;
	double	n;

	i = 0;
	while (s[i] && s[i] != '.')
		i++;
	md = i;
	if (s[i] && s[i] == '.')
		i++;
	while (s[i] && ft_isdigit(s[i]))
		i++;
	n = ft_atoi(s)+ ft_atoi(&s[md + 1]) * pow(10, - (i - md - 1));
	return (n);
}

void	parse_amb_light(char *line, t_data *info)
{
	char	**tmp;
	char	**tmp2;
	int		color[3];

	info->amb = malloc(sizeof(t_amb));
	if (!info->amb)
		return ;
	tmp = ft_split(line, ' ');
	info->amb->ratio = ft_atoi_float(tmp[1]);
	tmp2 = ft_split(tmp[2], ',');
	color[0] = ft_atoi(tmp2[0]);
	color[1] = ft_atoi(tmp2[1]);
	color[2] = ft_atoi(tmp2[2]);
	info->amb->trgb = get_trgb(0, color[0], color[1], color[2]);
	//clean this part later
	info->amb->r = color[0];
	info->amb->g = color[1];
	info->amb->b = color[2];
	// printf("amb light parsing check %d %d %d %f\n", info->amb->r, info->amb->g,info->amb->b, info->amb->ratio);
	free(tmp2);
	free(tmp);
	validity_check_amb_light(info);
}

void	change_white(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '	')
			line[i] = ' ';
		i++;
	}
}

void	parser(char **argv, t_data *info)
{
	int		fd;
	char	*line;
	char	**tmp;

	fd = format_check(argv[1]);
	line = get_next_line(fd);
	// printf("%p\n", line);
	while (line)
	{
		change_white(line);
		if (line)
			check_form(line);
		tmp = ft_split(line, ' ');
		// printf("|%s|\n", tmp[0]);
		if (!ft_strncmp(tmp[0], "A", 2))
			parse_amb_light(line, info);
		else if (!ft_strncmp(tmp[0], "C", 2))
			parser_camera(line, info);
		else if (!ft_strncmp(tmp[0], "L", 2))
			parser_light(line, info);
		else if (!ft_strncmp(tmp[0], "pl", 3))
			parser_plane(line, info);
		else if (!ft_strncmp(tmp[0], "sp", 3))
			parser_sphere(line, info);
		else if (!ft_strncmp(tmp[0], "cy", 3))
			parser_cylinder(line, info);
		else if (ft_strlen(tmp[0]) > 1)
			error("Wrong Identifier");
		free(line);
		destroy_split(tmp);
		line = get_next_line(fd);
	}
	if (!info->cam)
		error("NO CAMERA");
	if (!info->light)
		error("NO LIGHTS");
}
