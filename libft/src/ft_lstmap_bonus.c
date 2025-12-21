/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicli <vicli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:47:20 by vicli             #+#    #+#             */
/*   Updated: 2025/12/18 15:04:15 by vicli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_lstnew_safe(void *val)
{
	t_list	*new;

	if (val == NULL)
		return (NULL);
	new = ft_lstnew(val);
	if (new == NULL)
		free(val);
	return (new);
}

t_list	*ft_lstmap(t_list *l, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*new;

	if (l == NULL || f == NULL || del == NULL)
		return (NULL);
	new = ft_lstnew_safe((*f)(l->content));
	if (new == NULL)
		return (NULL);
	head = new;
	while (l->next)
	{
		l = l->next;
		new->next = ft_lstnew_safe((*f)(l->content));
		if (new->next == NULL)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		new = new->next;
	}
	return (head);
}
