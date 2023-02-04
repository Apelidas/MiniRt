
#include"../miniRT.h"

int	format_check(char *s)
{
	int	l;
	int	fd;

	l = ft_strlen(s);
	if (s[l - 2] && s[l - 1] && s[l - 3] && (s[l - 3] != '.' \
		|| s[l - 2] != 'r' || s[l - 1] != 't'))
		error("wrong format.");
	fd = open(s, O_RDONLY);
	if (fd < 0)
		error("unable to open the input.");
	return (fd);
}

int	skip_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	return (i);
}

int	is_normal_vector(t_vec3d	*norm)
{
	if (vec3d_len(norm) == 1)
		return (1);
	return (0);
}

void	is_color(int r, int g, int b)
{
	if (r > 255 || r < 0 || g > 255 \
		|| g < 0 || b > 255 || b < 0)
		error("color out of range."); ///implement this later
}

void	validity_check_amb_light(t_data *info)
{
	if (info->amb->ratio > 1 || info->amb->ratio < 0)
		error("ambient light ratio not in range.");
}

void	check_form(char *line)
{
	int	i;

	i = 1;
	while (line[i])
	{
		if (line[i] && line[i + 1] && line[i] == ',' \
			&& !ft_isdigit(line[i + 1]) && line[i + 1] != '-')
			error("Invalid space between ','");
		else if (line[i] && line[i - 1] && line[i] == ',' \
			&& !ft_isdigit(line[i - 1]) && line[i - 1] != '-')
			error("Invalid space between ','");
		i++;
	}
}
