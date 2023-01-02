/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkleinsc <kkleinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:14:25 by kkleinsc          #+#    #+#             */
/*   Updated: 2022/01/10 21:01:54 by kkleinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
	{
		return (0);
	}
	while (n > 1 && *s1 == *s2 && *s1 != '\0')
	{
		s1++;
		s2++;
		n--;
	}
	return ((unsigned char)s1[0] - (unsigned char)s2[0]);
}
