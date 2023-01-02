/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkleinsc <kkleinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:21:39 by kkleinsc          #+#    #+#             */
/*   Updated: 2022/01/10 13:23:44 by kkleinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*suc;
	t_list	*help;

	if (!lst || !f)
		return (NULL);
	suc = ft_lstnew(lst->content);
	help = suc;
	while (lst)
	{
		help->content = f(help->content);
		if (!help->content)
		{
			ft_lstclear(&suc, del);
			return (NULL);
		}
		lst = lst->next;
		if (!lst)
			break ;
		help->next = ft_lstnew(lst->content);
		help = help->next;
	}
	return (suc);
}
