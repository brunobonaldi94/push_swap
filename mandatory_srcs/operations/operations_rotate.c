/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 02:57:46 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/26 21:51:03 by bbonaldi         ###   ########.fr       */
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

int	ft_rotate_stack_rab(t_stack *stack)
{
	if (ft_head_is_null(stack->head_stack)
		|| ft_is_single_node(stack->head_stack))
		return (FALSE);
	if (ft_has_two_nodes(stack->head_stack))
	{
		ft_swap_stack(stack);
		return (TRUE);
	}
	ft_rotate_stack(stack);
	return (TRUE);
}

int	ft_rotate_stack_rr(t_stack *stack_a, t_stack *stack_b)
{
	int	first_rotate_return;
	int	second_rotate_return;

	first_rotate_return = ft_rotate_stack_rab(stack_a);
	second_rotate_return = ft_rotate_stack_rab(stack_b);
	return (first_rotate_return || second_rotate_return);
}

