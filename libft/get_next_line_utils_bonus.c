/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkleinsc <kkleinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:16:22 by kkleinsc          #+#    #+#             */
/*   Updated: 2022/10/31 15:00:50 by kkleinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	search_str(char *string, char del)
{
	int	i;

	i = 0;
	while (*string && *string != del)
	{
		string++;
		i++;
	}
	if (*string == '\n')
		i++;
	return (i);
}

void	strcut(char *tocut)
{
	int		size;
	int		i;
	int		len;

	len = search_str(tocut, '\n');
	size = search_str(tocut, '\0') + 1;
	i = 0;
	while (i < (size - len))
	{
		tocut[i] = tocut[len + i];
		i++;
	}
	while (tocut[i])
	{
		tocut[i] = '\0';
		i++;
	}
}

static int	help(char *front)
{
	int	flen;

	if (!front)
		flen = 0;
	else
		flen = search_str(front, '\0');
	return (flen);
}

char	*stradd(char *front, char *back, int blen)
{
	char	*out;
	int		flen;
	int		i;

	flen = help(front);
	out = malloc(sizeof(char) * (flen + blen + 1));
	if (!out)
		return (NULL);
	i = 0;
	while (i < flen)
	{
		out[i] = front[i];
		i++;
	}
	i = 0;
	while (i < blen)
	{
		out[flen + i] = back[i];
		i++;
	}
	out[flen + i] = '\0';
	if (front)
		free(front);
	return (out);
}
