/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_rotate_reverse.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 02:57:46 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/02 03:53:02 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_rotate_reverse_stack(t_double_list **head)
{
	t_double_list	*last;

	last = ft_find_last(*head);
	(*head)->prev = last;
	last->next = (*head);
	last->prev->next = NULL;
	last->prev = NULL;
	(*head) = last;
}

void	ft_rotate_stack_rrab(t_double_list **head)
{
	if (ft_check_head_nulish(head) || ft_is_single_node(head))
		return ;
	if (ft_has_two_nodes(head))
	{
		ft_swap_stack_sab(head);
		return ;
	}
	ft_rotate_reverse_stack(head);
}

void	ft_rotate_stack_rrr(t_double_list **head_a, t_double_list **head_b)
{
	ft_rotate_stack_rrab(head_a);
	ft_rotate_stack_rrab(head_b);
}