
#include"../miniRT.h"

void	format_check(char *s)
{
	int	l;
	l = ft_strlen(s);
	if (s[l - 2] && s[l - 1] && s[l - 3] && (s[l - 3] != '.' \
		|| s[l - 2] != 'r' || s[l - 1] != 't'))
		error("wrong format.");
}

int skip_spaces(char *s)
{
	int	i;
	
	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	return (i);
}

// int	skip_comma(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while(s[i] && s[i] == ',')
// 		i++;
// 	return (i);
// }