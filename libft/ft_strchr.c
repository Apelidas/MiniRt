/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkleinsc <kkleinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:59:45 by kkleinsc          #+#    #+#             */
/*   Updated: 2022/01/11 10:16:53 by kkleinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			*p;
	unsigned char	comp;

	comp = c;
	p = NULL;
	while (*s)
	{
		if (*s == comp)
		{
			p = (char *)s;
			break ;
		}
		s++;
	}
	if (*s == comp)
	{
		p = (char *)s;
	}
	return (p);
}
