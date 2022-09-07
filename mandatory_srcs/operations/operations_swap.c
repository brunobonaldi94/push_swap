/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_swap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 01:29:44 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/07 19:33:32 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_swap_stack(t_double_list **head)
{
	t_double_list	*temp;

	temp = (*head)->next;
	(*head)->next = temp->next;
	(*head)->prev = temp;
	temp->next = (*head);
	temp->prev = NULL;
	if ((*head)->next != NULL)
		(*head)->next->prev = (*head);
	(*head) = temp;
}

void	ft_swap_stack_sab(t_double_list **head)
{
	if (ft_check_head_nulish(head) || ft_is_single_node(head))
		return ;
	ft_swap_stack(head);
}

void	ft_swap_stack_ss(t_double_list **head_first, t_double_list **head_second)
{
	ft_swap_stack_sab(head_first);
	ft_swap_stack_sab(head_second);
}