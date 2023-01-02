/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkleinsc <kkleinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:16:18 by kkleinsc          #+#    #+#             */
/*   Updated: 2022/01/11 10:17:39 by kkleinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
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
		}
		s++;
	}
	if (*s == comp)
	{
		p = (char *)s;
	}
	return (p);
}
