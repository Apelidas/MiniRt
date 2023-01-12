
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
		error("color out of range.");
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
