/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_linked_list_utils_II.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 01:24:15 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/26 19:40:05 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_has_two_nodes(t_double_list *head)
{
	if (head->next == NULL)
		return (FALSE);
	if (head->next->next == NULL && head->prev == NULL)
		return (TRUE);
	return (FALSE);
}

t_double_list	*ft_find_last(t_double_list *head)
{
	if (ft_head_is_null(head))
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

t_double_list	*ft_find_up_to_index(t_double_list *head, int max_index)
{
	if (ft_head_is_null(head))
		return (NULL);
	while (head->next && max_index)
	{
		head = head->next;
		max_index--;
	}
	return (head);
}

int	ft_stack_is_empty(t_stack *stack)
{
	return (stack->size == 0);
}