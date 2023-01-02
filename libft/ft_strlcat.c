/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkleinsc <kkleinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:09:53 by kkleinsc          #+#    #+#             */
/*   Updated: 2022/01/10 14:09:57 by kkleinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	ldest;
	size_t	lsrc;
	size_t	i;

	i = 0;
	ldest = ft_strlen(dest);
	lsrc = ft_strlen(src);
	if (size == 0)
	{
		return (lsrc);
	}
	else if (size < ldest)
		return (lsrc + size);
	else
	{
		while (ldest + i + 1 < size && src[i])
		{
			dest[ldest + i] = src[i];
			i++;
		}
			dest[ldest + i] = 0;
		return (ldest + lsrc);
	}
}
