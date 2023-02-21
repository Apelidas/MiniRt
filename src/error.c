/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 22:54:16 by pooneh            #+#    #+#             */
/*   Updated: 2023/02/21 22:54:19 by pooneh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"
/**
 * @brief 
 * 
 * @param message 
 * @return void* 
 */
void	*error(char *message)
{
	write(2, "ERROR\n", 6);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	return (NULL);
}

int	error_int(char *message)
{
	write(2, "ERROR\n", 6);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	return (0);
}
