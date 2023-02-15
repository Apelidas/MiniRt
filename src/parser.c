#include"../miniRT.h"

double	ft_atoi_float(char *s)
{
	int		i;
	int		neg;
	int		md;
	double	n;

	i = 0;
	neg = 1;
	if (s[0] == '-')
		neg = -1;

	while (s[i] && s[i] != '.')
		i++;
	md = i;
	if (s[i] && s[i] == '.')
		i++;
	while (s[i] && ft_isdigit(s[i]))
		i++;
	n = ft_atoi(s)+ ft_atoi(&s[md + 1]) * pow(10, - (i - md - 1));
	if ((neg < 0 && n > 0))
		n *= neg;
	return (n);
}

int	parse_amb_light(char *line, t_data *info)
{
	char	**tmp;
	char	**tmp2;
	int		color[3];

	if (info->amb)
		return (error_int("multiple amb detected"));
	info->amb = malloc(sizeof(t_amb));
	if (!info->amb)
		return (error_int("malloc amb"));
	tmp = ft_split(line, ' ');
	if (!tmp || split_len(tmp) != 3)
		return (error_int("missing amb info"));
	info->amb->ratio = ft_atoi_float(tmp[1]);
	tmp2 = ft_split(tmp[2], ',');
	if (!tmp2 || split_len(tmp2) != 3)
		return (error_int("missing amb info"));
	color[0] = ft_atoi(tmp2[0]);
	color[1] = ft_atoi(tmp2[1]);
	color[2] = ft_atoi(tmp2[2]);
	info->amb->trgb = get_trgb(0, color[0], color[1], color[2]);
	info->amb->r = color[0];
	info->amb->g = color[1];
	info->amb->b = color[2];
	destroy_split(tmp2);
	destroy_split(tmp);
	return (validity_check_amb_light(info));
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

static void	parser_norm(t_data *info, char *line, char **tmp, int *check)
{
	if (!ft_strncmp(tmp[0], "A", 2))
		*check = parse_amb_light(line, info);
	else if (!ft_strncmp(tmp[0], "C", 2))
		*check = parser_camera(line, info);
	else if (!ft_strncmp(tmp[0], "L", 2))
		*check = parser_light(line, info);
	else if (!ft_strncmp(tmp[0], "pl", 3))
		*check = parser_plane(line, info);
	else if (!ft_strncmp(tmp[0], "sp", 3))
		*check = parser_sphere(line, info);
	else if (!ft_strncmp(tmp[0], "cy", 3))
		*check = parser_cylinder(line, info);
	else if (ft_strlen(tmp[0]) > 1)
		*check = error_int("Wrong Identifier");
}

void	*parser(char **argv, t_data *info)
{
	int		fd;
	char	*line;
	char	**tmp;
	int		check;

	fd = format_check(argv[1]);
	if (fd == 0)
		return (0);
	line = get_next_line(fd);
	check = 1;
	while (line)
	{
		change_white(line);
		if (line)
			check_form(line);
		tmp = ft_split(line, ' ');
		parser_norm(info, line, tmp, &check);
		free(line);
		destroy_split(tmp);
		if (!check)
			return (NULL);
		line = get_next_line(fd);
	}
	if (!info->cam)
		return (error("NO CAMERA"));
	if (!info->light)
		return (error("NO LIGHTS"));
	return (tmp);
}
