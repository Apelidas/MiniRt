/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkleinsc <kkleinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:14:30 by kkleinsc          #+#    #+#             */
/*   Updated: 2022/03/28 14:58:21 by kkleinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

void	ft_vartype(va_list *input, char c, int *outlen)
{
	if (c == 'c')
	{
		c = va_arg(*input, int);
		write(1, &c, 1);
		*outlen = *outlen + 1;
	}
	else if (c == 's')
		ft_string(va_arg(*input, char *), outlen);
	else if (c == 'p')
		ft_void(va_arg(*input, void *), outlen);
	else if (c == 'd' || c == 'i')
		ft_int((long int) va_arg(*input, int), outlen);
	else if (c == 'u')
		ft_int((long int) va_arg(*input, unsigned int), outlen);
	else if (c == 'x')
		ft_hex(va_arg(*input, unsigned int), 32, outlen);
	else if (c == 'X')
		ft_hex(va_arg(*input, unsigned int), 0, outlen);
	else
	{
		write(1, &c, 1);
		*outlen = *outlen + 1;
	}
}

int	ft_printf(const char *toprint, ...)
{
	va_list	input;
	int		outlen;

	outlen = 0;
	va_start(input, toprint);
	while (*toprint)
	{
		if (*toprint == '%')
		{
			toprint++;
			ft_vartype(&input, *toprint, &outlen);
		}
		else
		{
			write(1, toprint, 1);
			outlen++;
		}
		toprint++;
	}
	va_end(input);
	return (outlen);
}
