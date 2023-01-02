/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkleinsc <kkleinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:14:06 by kkleinsc          #+#    #+#             */
/*   Updated: 2022/01/10 15:05:24 by kkleinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*delete;

	if ((*del))
	{
		while (*lst)
		{
			delete = *lst;
			*lst = (*lst)->next;
			ft_lstdelone(delete, (*del));
		}
		*lst = NULL;
	}
}
