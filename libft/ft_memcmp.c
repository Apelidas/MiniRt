/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkleinsc <kkleinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:28:42 by kkleinsc          #+#    #+#             */
/*   Updated: 2022/01/10 13:28:48 by kkleinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (n == 0)
	{
		return (0);
	}
	while (((unsigned char *)s1)[0] == ((unsigned char *)s2)[0] && n > 1)
	{
		s1++;
		s2++;
		n--;
	}
	return (((unsigned char *)s1)[0] - ((unsigned char *)s2)[0]);
}
