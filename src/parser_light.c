#include"../miniRT.h"

void	validity_check_light(t_data *info)
{
	if (info->light->bright > 1 || info->light->bright < 0)
		error ("invalid brightness ratio.");
}

void	parser_light_helper(t_data *info, char *tmp, int indicator)
{
	if (indicator == 0)
		info->light->pos->x = ft_atoi_float(tmp);
	if (indicator == 1)
		info->light->pos->y = ft_atoi_float(tmp);
	if (indicator == 2)
		info->light->pos->z = ft_atoi_float(tmp);
	if (indicator == 3)
		info->light->bright = ft_atoi_float(tmp);
	//add the bonus light colors here later
}

void	parser_light(char *line, t_data *info)
{
	int		i;
	char	*tmp;
	int		indicator;

	i = skip_spaces(line) + 1;
	indicator = 0;
	if (line[i - 1] != 'L')
		error("wrong format.");
	while (line[i])
	{
		tmp = meaningful_string(line, i + skip_spaces(line + i));
		i += skip_spaces(line + i) + ft_strlen(tmp) \
			+ skip_spaces(line + i + ft_strlen(tmp));
		parser_light_helper(info, tmp, indicator);
		indicator++;
		if (line[i] && line[i] == ',')
			i++;
		if (indicator == 4)
			break ;
	}
	validity_check_light(info);
}
