
#include"../miniRT.h"

void	format_check(char *s)
{
	int	l;

	l = ft_strlen(s);
	if (s[l - 2] && s[l - 1] && s[l - 3] && (s[l - 3] != '.' \
		|| s[l - 2] != 'r' || s[l - 1] != 't'))
		error("wrong format.");
}

int	skip_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	return (i);
}

void	validity_check_amb_light(t_data *info)
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