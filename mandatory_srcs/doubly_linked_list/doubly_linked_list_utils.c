/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_linked_list_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 01:24:15 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/11 23:54:06 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_initialize_stack(t_stack *stack)
{
	stack->head_stack = NULL;
	stack->size = 0;
	stack->min = 0;
	stack->max = 0;
}

int	ft_head_is_null(t_double_list *head)
{
	return (head == NULL);
}

int	ft_is_single_node(t_double_list *head)
{
	if (head->next == NULL && head->prev == NULL)
		return (TRUE);
	return (FALSE);
}
