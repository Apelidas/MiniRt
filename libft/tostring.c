/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tostring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkleinsc <kkleinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 15:32:54 by kkleinsc          #+#    #+#             */
/*   Updated: 2022/03/28 14:51:55 by kkleinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	ft_hexchar(int val, int cas)
{
	if (val < 0)
		val = val * (-1);
	if (val < 10)
		return (val + '0');
	val = val - 10;
	return (65 + val + cas);
}

void	ft_hex(unsigned long long int n, int cas, int *outlen)
{
	char	c;

	c = ft_hexchar(n % 16, cas);
	n = n / 16;
	if (n != 0)
		ft_hex(n, cas, outlen);
	write(1, &c, 1);
	*outlen += 1;
}

void	ft_int(long int n, int *outlen)
{
	char	c;

	if (n < 0)
	{
		write(1, "-", 1);
		*outlen += 1;
		n = n * (-1);
	}
	c = (n % 10) + '0';
	n = n / 10;
	if (n > 0)
		ft_int(n, outlen);
	write(1, &c, 1);
	*outlen += 1;
}
