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
	i++;
	while (s[i] && ft_isdigit(s[i]))
		i++;
	n = ft_atoi(s)+ ft_atoi(&s[md + 1]) * pow(10, - (i - md - 1));
	return (n);
}

char	*meaningful_string(char *line, int i)
{
	char	*tmp;
	int		j;

	j = 0;
	tmp = malloc(ft_strlen(line));
	ft_bzero(tmp, ft_strlen(line));
	if (line[i] == ',')
		i++;
	while (line[i] && line[i] != ' ' && line[i] != ',')
	{
		tmp[j] = line[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

void	validity_check(t_data *info)
{
	if (info->amb->ratio > 1 || info->amb->ratio < 0)
		error("ambient light ratio not in range.");
	if (info->amb->r > 255 || info->amb->r < 0)
		error("ambient light red paramether not in range.");
	if (info->amb->g > 255 || info->amb->g < 0)
		error("ambient light green paramether not in range.");
	if (info->amb->b > 255 || info->amb->b < 0)
		error("ambient light blue paramether not in range.");
}

void	parse_light_helper(t_data *info, int indicator, char *tmp)
{
	if (indicator == 0)
			info->amb->ratio = ft_atoi_float(tmp);
	else if (indicator == 1)
		info->amb->r = ft_atoi_float(tmp);
	else if (indicator == 2)
		info->amb->g = ft_atoi_float(tmp);
	else if (indicator == 3)
		info->amb->b = ft_atoi_float(tmp);
}

void	parse_light(char *line, t_data *info)
{
	int		i;
	char	*tmp;
	int		indicator;

	indicator = 0;
	i = skip_spaces(line) + 1;
	if (line[i - 1] != 'A')
		error("wrong format.");
	while (line[i])
	{
		tmp = meaningful_string(line, i + skip_spaces(line + i));
		i += skip_spaces(line + i) + ft_strlen(tmp) \
			+ skip_spaces(line + i + ft_strlen(tmp));
		parse_light_helper(info, indicator, tmp);
		indicator++;
		if (line[i] && line[i] == ',')
			i++;
		if (indicator == 4)
			break ;
	}
	free(tmp);
	validity_check(info);
}

void	parser(char **argv, t_data *info)
{
	int		fd;
	char	*line;

	format_check(argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error("unable to open the input.");
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strchr(line, 'A'))
			parse_light(line, info);
		line = get_next_line(fd);
	}
}