/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkleinsc <kkleinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:06:11 by kkleinsc          #+#    #+#             */
/*   Updated: 2022/03/28 14:55:42 by kkleinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

void	ft_vartype(va_list *input, char c, int *outlen);
int		ft_printf(const char *toprint, ...);
void	ft_string(char *toprint, int *outlen);
void	ft_int(long int toprint, int *outlen);
void	ft_hex(unsigned long long int n, int cas, int *outlen);
void	ft_void(void *val, int *outlen);

#endif