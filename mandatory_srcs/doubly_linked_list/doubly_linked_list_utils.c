/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_linked_list_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 01:24:15 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/01 03:24:48 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_initialize_stack(t_stack *stack)
{
	stack->head_stack = NULL;
	stack->size = 0;
}

int	ft_has_no_head(t_double_list **head)
{
	return (head == NULL);
}

int	ft_head_is_null(t_double_list **head)
{
	return ((*head) == NULL);
}

int	ft_check_head_nulish(t_double_list **head)
{
	return (ft_has_no_head(head) || ft_head_is_null(head));
}

int	ft_is_single_node(t_double_list **head)
{
	if ((*head)->next == NULL && (*head)->prev == NULL)
		return (TRUE);
	return (FALSE);
}