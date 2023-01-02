/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkleinsc <kkleinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:04:36 by kkleinsc          #+#    #+#             */
/*   Updated: 2022/01/10 15:12:20 by kkleinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*copy;
	int		i;

	i = 0;
	copy = ft_calloc(ft_strlen(s1) + 1, sizeof(char));
	if (!copy)
	{
		return (NULL);
	}
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	return (copy);
}
