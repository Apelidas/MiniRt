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
	int		i;
	int		color[3];

	tmp = ft_split(line, ' ');
	i = 0;
	while (tmp[i])
	{
		if (i == 1)
			info->amb->ratio = ft_atoi_float(tmp[i]);
		if (i == 2)
			color[0] = ft_atoi(tmp[i]);
		if (i == 3)
			color[1] = ft_atoi(tmp[i]);
		if (i == 4)
			color[2] = ft_atoi(tmp[i]);
		i++;
	}
	info->amb->trgb = get_trgb(0, color[0], color[1], color[2]);
	//clean this part later
	info->amb->r = color[0];
	info->amb->g = color[1];
	info->amb->b = color[2];
	free(tmp);
	validity_check_amb_light(info);
}

void	parser(char **argv, t_data *info)
{
	int		fd;
	char	*line;
	char	**tmp;

	fd = format_check(argv[1]);
	line = get_next_line(fd);
	while (line)
	{
		if (line)
			check_form(line);
		tmp = ft_split(line, ' ');
		if (!ft_strncmp(tmp[0], "A", ft_strlen(tmp[0])))
			parse_amb_light(line, info);
		if (!ft_strncmp(tmp[0], "C", ft_strlen(tmp[0])))
			parser_camera(line, info);
		if (!ft_strncmp(tmp[0], "L", ft_strlen(tmp[0])))
			parser_light(line, info);
		if (!ft_strncmp(tmp[0], "pl", ft_strlen(tmp[0])))
			parser_plane(line, info);
		if (!ft_strncmp(tmp[0], "sp", ft_strlen(tmp[0])))
			parser_sphere(line, info);
		if (!ft_strncmp(tmp[0], "cy", ft_strlen(tmp[0])))
			parser_cylinder(line, info);
		line = get_next_line(fd);
	}
}
