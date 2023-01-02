/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkleinsc <kkleinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:26:39 by kkleinsc          #+#    #+#             */
/*   Updated: 2022/01/11 12:43:11 by kkleinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	void			*p;
	unsigned char	comp;

	comp = c;
	p = NULL;
	if (n == 0)
	{
		return (p);
	}
	else
	{
		while (n > 0)
		{
			if (((unsigned char *)s)[0] == comp)
			{
				p = (unsigned char *)s;
				break ;
			}
			s++;
			n--;
		}
		return (p);
	}
}
