/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkleinsc <kkleinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:15:16 by kkleinsc          #+#    #+#             */
/*   Updated: 2022/01/11 12:45:17 by kkleinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_loops(const char *s, const char *sub, size_t n)
{
	int		i;
	char	*bs;

	bs = NULL;
	i = 0;
	while (*s && n > 0)
	{
		if (*s == sub[i])
		{
			while (s[i] == sub[i] && n - i > 0 && sub[i])
			{
				i++;
			}
			if (sub[i] == 0)
			{
				bs = (char *)s;
				break ;
			}
			i = 0;
		}
		s++;
		n--;
	}
	return (bs);
}

char	*ft_strnstr(const char *s, const char *sub, size_t n)
{
	char	*bs;

	bs = NULL;
	if (*sub == 0)
		return ((char *)s);
	if (n > 0)
		bs = ft_loops(s, sub, n);
	return (bs);
}
