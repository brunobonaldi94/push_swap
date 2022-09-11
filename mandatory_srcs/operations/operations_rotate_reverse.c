/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_rotate_reverse.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 02:57:46 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/11 23:32:46 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_rotate_reverse_stack(t_stack *stack)
{
	t_double_list	*last;

	last = ft_find_last(stack->head_stack);
	stack->head_stack->prev = last;
	last->next = stack->head_stack;
	last->prev->next = NULL;
	last->prev = NULL;
	stack->head_stack = last;
}

void	ft_rotate_stack_rrab(t_stack *stack)
{
	if (ft_head_is_null(stack->head_stack)
		|| ft_is_single_node(stack->head_stack))
		return ;
	if (ft_has_two_nodes(stack->head_stack))
	{
		ft_swap_stack(stack);
		return ;
	}
	ft_rotate_reverse_stack(stack);
}

void	ft_rotate_stack_rrr(t_stack *stack_a, t_stack *stack_b)
{
	ft_rotate_stack_rrab(stack_a);
	ft_rotate_stack_rrab(stack_b);
}
