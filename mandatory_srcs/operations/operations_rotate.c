/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 02:57:46 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/07 20:38:49 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_rotate_stack(t_stack *stack)
{
	t_double_list	*last;

	last = ft_find_last(stack->head_stack);
	stack->head_stack->prev = last;
	last->next = stack->head_stack;
	stack->head_stack->next->prev = NULL;
	stack->head_stack = stack->head_stack->next;
	last->next->next = NULL;
}

void	ft_rotate_stack_rab(t_stack *stack)
{
	if (ft_head_is_null(stack->head_stack) || ft_is_single_node(stack->head_stack))
		return ;
	if (ft_has_two_nodes(stack->head_stack))
	{
		ft_swap_stack(stack);
		return ;
	}
	ft_rotate_stack(stack);
}

void	ft_rotate_stack_rr(t_stack *stack_a, t_stack *stack_b)
{
	ft_rotate_stack_rab(stack_a);
	ft_rotate_stack_rab(stack_b);
}