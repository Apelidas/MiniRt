/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkleinsc <kkleinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:17:28 by kkleinsc          #+#    #+#             */
/*   Updated: 2022/01/10 15:02:22 by kkleinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_forward(char const *s1, char const *set)
{
	int	i;
	int	pos;

	pos = 0;
	while (*s1)
	{
		i = 0;
		while (set[i])
		{
			if (*s1 == set[i])
			{
				s1++;
				pos++;
				break ;
			}
			i++;
		}
		if (!set[i])
		{
			break ;
		}
	}
	return (pos);
}

static int	ft_backward(char const *s1, char const *set, size_t len)
{
	size_t	pos;
	int		i;

	pos = 0;
	i = 0;
	while (len - pos > 0 && set[i])
	{
		i = 0;
		while (set[i])
		{
			if (s1[len - pos] == set[i])
			{
				pos++;
				break ;
			}
			i++;
		}
	}
	return (pos);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	cut;
	size_t	end;
	char	*copy;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	cut = ft_forward(s1, set);
	end = ft_backward(s1, set, len - 1);
	copy = ft_substr(s1, cut, len - end - cut);
	if (copy == NULL)
		return (NULL);
	return (copy);
}
