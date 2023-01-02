/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkleinsc <kkleinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:10:48 by kkleinsc          #+#    #+#             */
/*   Updated: 2022/01/10 15:05:04 by kkleinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_filler(char *str, long int n, int len)
{
	if (n < 0)
		n = n * -1;
	while (len > 0)
	{
		len--;
		str[len] = (n % 10) + 48;
		n = n / 10;
	}
}

static int	ft_istrlen(int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = ft_istrlen(n);
	if (len == 0)
		len = 1;
	else if (n < 0)
		len++;
	str = ft_calloc((len + 1), sizeof(char));
	if (!str)
	{
		return (NULL);
	}
	ft_filler(str, n, len);
	if (n < 0)
		str[0] = '-';
	return (str);
}
