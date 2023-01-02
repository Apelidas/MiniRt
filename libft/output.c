/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkleinsc <kkleinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 15:07:26 by kkleinsc          #+#    #+#             */
/*   Updated: 2022/03/28 14:52:46 by kkleinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_string(char *toprint, int *outlen)
{
	if (!toprint)
	{
		write(1, "(null)", 6);
		*outlen += 6;
	}
	else
	{
		while (*toprint)
		{
			write(1, toprint, 1);
			*outlen += 1;
			toprint++;
		}
	}
}

void	ft_void(void *val, int *outlen)
{
	write(1, "0x", 2);
	*outlen = *outlen + 2;
	ft_hex((unsigned long long int) val, 32, outlen);
}
