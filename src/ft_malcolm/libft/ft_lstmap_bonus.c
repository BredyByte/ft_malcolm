/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 10:40:45 by dbredykh          #+#    #+#             */
/*   Updated: 2023/04/29 13:34:01 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*aux;
	t_list	*new;

	if (!lst)
		return (NULL);
	new = 0;
	while (lst)
	{
		aux = malloc(sizeof(t_list));
		if (!aux)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		else
		{
			aux->content = f(lst->content);
			aux->next = NULL;
			ft_lstadd_back(&new, aux);
			lst = lst->next;
		}
	}
	return (new);
}
