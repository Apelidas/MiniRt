/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkleinsc <kkleinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:08:03 by kkleinsc          #+#    #+#             */
/*   Updated: 2022/01/10 20:19:47 by kkleinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*combo;
	int		i;

	i = 0;
	if (!s1 ||!s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	combo = ft_calloc((len + 1), sizeof(char));
	if (!combo)
		return (NULL);
	while (*s1)
	{
		combo[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		combo[i] = *s2;
		s2++;
		i++;
	}
	return (combo);
}
