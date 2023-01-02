/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkleinsc <kkleinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:18:56 by kkleinsc          #+#    #+#             */
/*   Updated: 2022/01/11 12:53:43 by kkleinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_allocate(size_t len, size_t i)
{
	char	*sub;

	if (i >= len)
	{
		sub = malloc(sizeof(char) * (len +1));
	}
	else
	{
		sub = malloc(sizeof(char) * (i + 1));
	}
	return (sub);
}

char	*ft_substr(char const *s, size_t start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	sub = ft_allocate(len, i);
	if (!sub)
		return (NULL);
	if (start < i)
	{
		i = 0;
		while (s[start + i] && i < len)
		{
			sub[i] = s[start + i];
			i++;
		}
		sub[i] = '\0';
	}
	else
	{
		sub[0] = 0;
	}
	return (sub);
}
