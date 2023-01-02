/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkleinsc <kkleinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:42:28 by kkleinsc          #+#    #+#             */
/*   Updated: 2022/01/11 13:29:40 by kkleinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_splitcount(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (*s)
	{
		if ((*s == c || s[1] == '\0') && i != 0)
		{
			count++;
			i = 0;
		}
		else if (*s != c)
		{
			i++;
		}
		s++;
	}
	if (i > 0)
		count++;
	return (count);
}

static int	ft_strlenc(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s != c && *s)
	{
		i++;
		s++;
	}
	return (i);
}

static char const	*ft_copy(int len, char const *s, char **out, int pos)
{
	int	i;

	i = 0;
	while (i < len)
	{
		out[pos][i] = *s;
		s++;
		i++;
	}
	out[pos][i] = 0;
	return (s);
}

static int	ft_allocmatrix(char **out, int pos, int len)
{
	out[pos] = malloc(sizeof(char) * (len + 1));
	if (!out[pos])
	{
		while (pos >= 0)
		{
			free(out[pos]);
			pos--;
		}
		free(out);
		return (0);
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**out;
	int		len;
	int		pos;
	int		scount;

	pos = 0;
	if (!s)
		return (NULL);
	out = ft_calloc(((scount = ft_splitcount(s, c)) + 1), sizeof(char *));
	if (out == NULL)
		return (NULL);
	while (*s && pos < scount)
	{
		while (*s == c)
			s++;
		len = ft_strlenc(s, c);
		if (!ft_allocmatrix(out, pos, len))
			return (NULL);
		s = ft_copy(len, s, out, pos);
		pos++;
	}
	return (out);
}
