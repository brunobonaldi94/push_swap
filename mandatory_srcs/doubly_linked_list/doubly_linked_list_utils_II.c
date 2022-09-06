/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_linked_list_utils_II.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 01:24:15 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/06 03:57:40 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_has_two_nodes(t_double_list **head)
{
	if ((*head)->next == NULL)
		return (FALSE);
	if ((*head)->next->next == NULL && (*head)->prev == NULL)
		return (TRUE);
	return (FALSE);
}

t_double_list	*ft_find_last(t_double_list *head)
{
	if (ft_check_head_nulish(&head))
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}