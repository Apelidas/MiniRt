/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkleinsc <kkleinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:40:35 by kkleinsc          #+#    #+#             */
/*   Updated: 2022/01/10 13:40:43 by kkleinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	char	out;

	if (n == 0)
	{
		write(fd, "0", 1);
	}
	else if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n = n * -1;
		}
		if (n / 10 > 0)
		{
			ft_putnbr_fd(n / 10, fd);
		}
		out = (n % 10) + 48;
		write(fd, &out, 1);
	}
}
