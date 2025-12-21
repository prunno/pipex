/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicli <vicli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:41:17 by vicli             #+#    #+#             */
/*   Updated: 2025/12/18 15:04:16 by vicli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **head, void (*del)(void *))
{
	t_list	*current;
	t_list	*prev;

	if (head == NULL || *head == NULL || del == NULL)
		return ;
	prev = *head;
	current = prev->next;
	while (current)
	{
		ft_lstdelone(prev, del);
		prev = current;
		current = current->next;
	}
	ft_lstdelone(prev, del);
	*head = NULL;
}
