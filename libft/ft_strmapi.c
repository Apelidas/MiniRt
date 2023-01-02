/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkleinsc <kkleinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:13:13 by kkleinsc          #+#    #+#             */
/*   Updated: 2022/01/11 12:48:52 by kkleinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new;
	size_t	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	new = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (new == NULL)
	{
		return (NULL);
	}
	while (*s)
	{
		new[i] = f(i, *s);
		s++;
		i++;
	}
	new[i] = '\0';
	return (new);
}
